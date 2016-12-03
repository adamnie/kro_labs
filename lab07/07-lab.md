# Kierunki rozwoju Oprogramowania #
## Vagrant i Docker ##
### Uruchamianie i Instalacja ###
#### zapraszam na stronę http://dillinger.io/ - wklej tam treść pliku
#### Uruchom system ubuntu1610 a następnie wykonaj dalsze polecenia

##### Aktualizacja informacji o dostępnych paczkach, instalacja najnowszej dostępnej dla danego systemu wersji Dockera.

``` bash
sudo apt-get update
wget -qO- https://get.docker.com/ | sh
```

Aby móc wywoływać polecenia dla Dockera bez używania `sudo` należałoby dodać obecnego użytkownika do grupy docker (o ile już do niej nie należy - można to sprawdzić poleceniem `groups`)

``` bash
sudo usermod -aG docker `whoami`
```
Aby uprawnienia zostały zaktualizowane może zajść potrzeba ponownego zalogowania się.

##### Sprawdź czy demon Dockera działa
``` bash
systemctl status docker
```

### Wyczyść środowisko
``` bash
docker stop $(docker ps -q)
docker rm $(docker ps -a -q)
docker rmi $(docker images -q)
```

### Tworzymy własny kontener ###

Celem pierwszej części ćwiczenia jest pokazanie w jaki sposób można stworzyć środowisko deweloperskie wewnątrz kontenera i wykorzystując współdzielenie folderów pracować w nim bez konieczności używania dodatkowych narzędzi. W ćwiczeniu stworzymy kontener zawierający serwer node.js z własnymi paczkami, tak aby ich instalacja nie była przeprowadzana każdorazowo.

Pierwszą czynnością, która należy wykonać jest stworzenie pustego pliku `Dockerfile`, w którym będziemy umieszczać polecenia `COPY`, `FROM` itd.
``` bash
touch Dockerfile
```

Aby nie budować naszego kontenera całkiem od zera, zdefiniujemy na jakim obrazie będziemy bazować (nawet w przypadku budowania od zera bazuje się na pewnym obrazie. **Czy wiesz na jakim? Dowiedz się**). Wyszukaj pod adresem `https://hub.docker.com` dostępne obrazy z serwerem node.js i wybierz oficjalną. Następnie sprawdź jakie wersje obrazu są dostępne i wybierz najnowszy. Pamiętaj o tym, że tag `latest` nie jest dobrym wyborem. **Jak myślisz dlaczego?**. Poniżej przykład użycia dla obrazu `ubuntu 16.10` **(zmień nazwę obrazu i tag)**

``` Dockerfile
FROM ubuntu:yakkety
```


Następnie należy utworzyć folder który będzie zawierał naszą aplikację, a także przypiszemy ścieżkę do zmiennej systemowej (Dzięki temu docker będzie wiedział w jakiej lokacji będą wykonywane polecenia takie jak `ADD`, `RUN` czy `CMD`)

``` Dockerfile
RUN mkdir -p /usr/src
WORKDIR /usr/src/app
```

W kolejnym etapie posłużymy się gotowym plikiem `package.json` opracowanego przy poprzednim laboratorium. Zostanie on skopiowany do folderu z aplikacją, a następnie dodane zostaną wszystkie zależności w nim występujące.

``` Dockerfile
COPY node-app/package.json /usr/src/app
RUN npm install
```

Gdybyśmy nie chcieli dostarczać kontenera z gotową aplikacją w tym miejscu można by pominąć fragment kopiujący wszystkie pliki z lokalnego folderu do folderu aplikacji w kontenerze.

``` Dockerfile
COPY node-app/ /usr/src/app/
```

Powyższe polecenie skopiuje wszystkie pliki z katalogu z plikiem Dockerfile do katalogu aplikacji wewnątrz kontenera. Czasami jednak jest to niepożądane, ale z drugiej strony dodawanie folderów/plików explicite jest niewygodne. Znacznie łatwiej stworzyć plik który będzie zawierał informację jakich ścieżek nie chcemy kopiować. Plik ten ma nazwę `.dockerignore`. Każda linijka zawiera nazwę bądź wyrażenie regularne, które będzie czarną listą plików, które będą zignorowane (**Czy znasz jakieś inne środowisko które wykorzystuje podobny mechanizm?**).

Pozostało jeszcze powiedzieć `Dockerowi` jaki port ma być udostępniony dla innych aplikacji do mapowania.

``` Dockerfile
EXPOSE 3000
```

Na sam koniec należy pamiętać o tym co stanie się jeżeli nie podamy żadnej komendy jaka powinna zostać uruchomiona wewnątrz kontenera. W naszym przypadku taką komendą będzie

``` Dockerfile
CMD [ "npm", "start" ]
```

Mamy już gotowy plik. Teraz należy zbudować na jego podstawie obraz. Aby to zrobić należy wydać polecenie `docker build`. Dodatkowy argument pozwoli nam otagować nasz obraz aby łatwiej było nam później go odnaleźć i uruchomić.
``` bash
docker build -t user/app-name .
```

Przeanalizuj wyniki każdego z kroków jakie przeprowadza `docker`
Spróbuj uruchomić obraz.
``` bash
docker run -p 32233:3000 -d image-name
```

Uruchamianie się nie powiedzie ponieważ próbujemy uruchomić aplikację, której nie ma w kontenerze. Aby naprawić en problem możemy podmontować katalog z aplikacją (zakładam że aplikacja znajduje się w bieżącym katalogu w podkatalogu `app`).

``` bash
docker run -p 32233:3000 -d -v ./app:/usr/src/app image-name
```

Sprawdz działanie serwera. Jeżeli wciąż się nie uruchamia, to spróbuj zamienić `-d` na `-ti` aby sprawdzić wynik działania w trybie interaktywnym.

Jak pewnie zauważyłeś problemem jest brak połączenia z serwerem `mongodb`. Uruchomimy go jednak w osobnym kontenerze.

``` bash
docker run -p 27100:27017 -d mongo:3.1
```

Jak widzisz przeprowadzone zostało mapowanie portów. W przypadku pojedynczej aplikacji nie jest to konieczne, jednak gdy będziesz zarządzał wieloma kontenerami może okazać się to niezbędne.
Gdybyś teraz spróbował dodać dodatkowe mapowanie docker nie będzie w stanie uruchomić kontenera ze względu na to iż port jest już w użyciu. Jak zatem powiedzieć kontenerowi `node.js`, że baza mongo jest widoczna w innym kontenerze?

#### Linkowanie kontenerów ####

Najproszą metodą jest wykorzystanie istniejących mechanizmów. Mowa tutaj o opcji `--link` którą dodajemy do polecenia dockera. Powoduje ona że porty wystawione przez kontener podlinkowany (zmienna `EXPOSE`) będą dostępne dla uruchamianego kontenera. Należy jednak wziąć pod uwagę, że nie będą to porty kontenera tzn nie możemy się do nich odwołać `localhost:27017`. Aby kontener wiedział o adresie udostępnianej usługi należy podać jej wewnętrzną nazwę (przykład poniżej). Tak jak w przypadku innych poleceń dockera podajemy wartości rozdzielone `:`. W tym przypadku jest to id lub nazwa kontenera oraz nazwa hosta pod jaką będzie on widoczny w środku uruchamianego kontenera. Jeżeli spróbujesz uruchomić ten przykład, możesz być niemal pewien że nie zadziała.

``` bash
docker run -p 32233:3000 --link <hash-value-or-name>:mongo -d -v ./app:/usr/src/app image-name
```  

Powodem jest adres serwera mongodb jaki podałeś w pliku konfiguracyjnym aplikacji. Aby odwołanie było poprawne możesz go zmienić na stałą wartość `mongo`. Lepszym wyjściem (i bardziej uniwersalnym) byłoby pobieranie tego adresu i portu ze zmiennych systemowych. W aplikacji node.js można to zrobić poprzez `process.env.VARIABLE_NAME`. Ustawienie zmiennych systemowych dla uruchamianego kontenera dokonujemy poprzez dodanie parametru `-e`, np: `-e MONGO_DB_HOST=mongo -e MONGO_DB_PORT=21333`

### Vagrant ###
Vagrant umożliwia zarządzanie wirtualnymi maszynami i kontenerami. W przypadku środowiska, które nie wspiera dockera natywnie możemy zdefiniować wirtualną maszynę wewnątrz której docker zostanie uruchomiony. W naszym przypadku nie zachodzi taka potrzeba.

Instalacja
```bash
sudo apt-get install vagrant
```

#### Node.js + Mongo ####

Stwórz folder w którym będą znajdowały się pliki `DockerHostVagrantfile` i `Vagrantfile`

Plik `DockerHostVagrantfile` zawiera konfigurację hosta uruchamianego jako maszyna wirtualna w momencie, w którym Docker nie jest natywnie wspierany. Listę dostępnych obrazów można znaleźć na stronie `https://atlas.hashicorp.com/boxes/search`

`DockerHostVagrantfile`
``` bash
Vagrant.configure("2") do |config|
  config.vm.provision "docker"
  config.vm.define "dockerhost"
  config.vm.box = "ubuntu/trusty64"
  config.vm.network "forwarded_port",
    guest: 8080, host: 8080
  config.vm.provider :virtualbox do |vb|
      vb.name = "dockerhost"
  end
end
```

Poniższy plik zawiera definicję uruchamianych kontenerów.

Uzupełnij pola `image`, `ports` i `volumes`

`Vagrantfile`
``` bash

Vagrant.configure("2") do |config|
    config.vm.define "mongodev" do |a|
    a.vm.provider "docker" do |d|
      d.image = ""
      d.name = "mongodev"
      d.create_args = ["-d"]
      d.ports = [":"]
      d.remains_running = true
      d.vagrant_machine = "dockerhost"
      d.vagrant_vagrantfile = "./DockerHostVagrantfile"
    end
  end

  config.vm.define "nodedev" do |a|
    a.vm.provider "docker" do |d|
      d.image = ""
      d.name = "nodedev"
      d.link("mongodev:mongo")
      d.ports = [""]
      d.volumes = [""]
      d.remains_running = false
      d.vagrant_machine = "dockerhost"
      d.vagrant_vagrantfile = "./DockerHostVagrantfile"
    end
  end

end
```

Aby uruchomić `Vagranta` należy wydać polecenie:
`vagrant up --no-parallel`
Aby uruchomić pojedynczy kontener z poziomu `Vagranta` należy dodać jego nazwę na końcu polecenia.
Po udanym uruchomieniu maszyny wirtualnej sprawdź wyniki poleceń `vagrant docker-logs` i `docker ps`
Sprawdź czy serwis jest dostępny z poziomu przeglądarki.
