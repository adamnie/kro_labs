#### Sprawdź jaka jest pula adresów IP dostępnych dla Dokera.
`172.17.0.0/16`
#### Co to jest `docker.sock` i gdzie się znajduje?
`docker.sock is the UNIX socket that Docker daemon is listening to. It's the main entry point for Docker API. It also can be TCP socket but by default for security reasons Docker defaults to use UNIX socket.`
#### Jaki jest główny katalog Dockera?
`/etc/default/docker`

#### Dlaczego należy podać polecenie po nazwie obrazu?
`aby docker sie sam nie zakonczyl, polecenie zwórci sterowanie i utrzyma dockera przy zyciu`
#### Co oznaczają poszczególne opcje?
`-t              : Allocate a pseudo-tty
-i              : Keep STDIN open even if not attached`

#### Czy zauważyłeś coś szczególnego?

`Tak, pokazywane sa rowniez zatrzymane kontenery.I istnieją dodatkowe zabawne nazwy`

#### Zobacz czy możesz uruchomić zatrzymany kontener (`docker start`). Uruchom ponownie kontener (`docker run`) i sprawdź czy plik `file.dat` w nim istnieje.
`Tak istnieje.`

#### Sprawdź zawartość iptables - `iptables -L`
`Chain DOCKER (1 references)
target     prot opt source               destination         
ACCEPT     tcp  --  anywhere             172.17.0.3           tcp dpt:https
ACCEPT     tcp  --  anywhere             172.17.0.3           tcp dpt:http`

#### Sprawdź mapowanie portów poleceniem i wyświetl w przeglądarce odpowiednią stronę.
`docker ps`
