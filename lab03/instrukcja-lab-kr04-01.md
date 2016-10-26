# Kierunki rozwoju Oprogramowania #
## MEAN Stack ##
### Instalacja ###

``` bash
sudo apt-get update
sudo apt-get install nodejs npm mongodb
```

### Pierwszy projekt
``` bash
npm init
```
Przeanalizuj zawartość pliku **package.json**.

Wypakuj zawartość archiwum dostarczonego do laboratorium. W celu instalacji dpdatkowych modułów należy wydać polecenie
``` bash
npm install <nazwa-paczki> --save
```

Opcja save pozwala na dopisanie zależności do pliku konfiguracyjnego. Aby zainstalować wszystkie zależności dla modułu należy w katalogu z plikiem **package.json** wydać powyższe polecenie
``` bash
npm install
```

## Pliki projektu
### Uruchamianie serwera
W dołączonym do projektu pliku w katalogu bin znajduje się skrypt do uruchomienia serwera. Należy go wywoływać w następujący sposób:
```bash
DEBUG=cwierkacz ./bin/www
```

###Logika aplikacji
Pierwszą czynnością którą należy wykonać jest zazwyczaj stworzenie aplikacji Angular, która będzie zawierała funkcjonalność po stronie front endu. Plik taki umieszczamy w katalogu **public** aby wyraźnie odseparować go od logiki serwera. Następnie tworzymy przykładowe widoki `main.html`, `login.html`, i `register.html`, które także umieszczamy w katalogu **public**.

W pliku `JavaScript` umieszczonym w katalogu `public` tworzymy moduł, a następnie dodajemy do niego kontroler, który zajmie się podstawową funkcjonalnością aplikacji (wyświetlanie, dodawanie postów).

```javascript
//cwierkaczApp.js
var app = angular.module('cwierkaczApp', []);

app.controller('mainController', function(){
});
```
### Template
Naszym bazowym plikiem widoku będzie `main.html` umieszczony w katalogu `public`. Zawiera formularz do tworzenia nowych postów jak i listę ostatnich postów. W celu uproszczenia kodu na tym etapie nasza aplikacja będzie posiadała osobne pole do wprowadzania loginu.


```html
<!--main.html-->
<!doctype html>
<html>
  <head>
    <title>Ćwierkacz</title>
  </head>
  <body>
    <div id='main'>
      <form>
        <input type="text" placeholder="Nick" />
        <textarea required maxlength="200" rows="3" placeholder="Powiedź coś"></textarea>
        <input class="button" type="submit" value="Ćwierk!" />
      </form>
      <div id="post-stream">
        <h4>Ostatnie Ćwierki</h4>
              <!--Zostanie uzupełnione przez logikę aplikacji-->
        </div>
      </div>
    </div>
  </body>
</html>
```
Teraz pozostało kedynie podpięcie template'a do aplikacji.

Najpierw należy jednak dołączyć pliki frameworka i aplikacji (część frontendowa) do widoku. Następnie dodajemy dyrektywę `ng-app` do jednego z elementów drzewa DOM naszego widoku. Po tym należy jeszcze dodać dyrektywę `ng-controller` do elementu zawartego w aplikacji (wewnątrz `ng-app`) i jako argument przekazać nazwę kontrolera.

```html
<!--main.html-->
<!doctype html>
<html>
  <head>
    <title>Ćwierkacz</title>
    <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.5.8/angular.min.js"></script>
    <script src="javascripts/cwierkaczApp.js"></script>
  </head>
  <body ng-app="cwierkaczApp">
    <div id='main' ng-controller="mainController">
        ...
    </div>
  </body>
</html>
```

### Łączymy model i widok
Teraz możemy tworzyć obiekty w kontrolerze, które będą dowiązane do widoku. Za pomocą zmiennej `$scope` przekazywanej do kontrolera ustawiamy obiekty w elemencie z pliku template'a.
Dodajmy tablicę `posts` do `$scope`. Stworzymy także nowy `newPost`. Stworzymy funkcję `post`, która doda zawartość naszego posta do tablicy za każdym razem kiedy użytkownik kliknie odpowiedni przycisk w widoku.

```javascript
//cwierkaczApp.js
var app = angular.module('cwierkaczApp', []);

app.controller('mainController', function($scope){
  $scope.posts = [];
  $scope.newPost = {created_by: '', text: '', created_at: ''};

  $scope.post = function(){
    $scope.newPost.created_at = Date.now();
    $scope.posts.push($scope.newPost);
    $scope.newPost = {created_by: '', text: '', created_at: ''};
  };
});
```

### Dowiązanie danych, filtrowanie
Aby Angular wiedział skąd wziąć zawarość do utworzenia nowego posta skorzystamy w pliku `main.html` z dyrektywy `ng-model`. Aby wyświetlić zawartość tablicy z postami użyjemy dyrektywy `ng-repeat`.
Posty zostaną posortowane po dacie utworzenia. Zauważ że dla elementów parzystych/nieparzystych ustawiamy różne klasy.


```html
<!--main.html-->
<html>
  <head>
    <title>Ćwierkacz</title>
    <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.5.8/angular.min.js"></script>
    <script src="javascripts/cwierkaczApp.js"></script>
  </head>
  <body ng-app="cwierkaczApp">
    <div id='main' ng-controller="mainController">
      <form ng-submit="post()">
        <input required type="text" placeholder="Nick" ng-model="newPost.created_by" />
        <textarea required maxlength="200" rows="3" placeholder="Powiedź coś"></textarea>
        <input class="button" type="submit" value="Ćwierk!" />
      </form>
      <div id="post-stream">
        <h4>Ostatnie Ćwierki</h4>
            <div class='post' ng-repeat="post in posts | orderBy:'created_at':true" ng-class-odd="'odd'" ng-class-even="'even'">
            <p>{{post.created_by}} says {{post.text}} at {{post.created_at}}</p>
            </div>
      </div>
    </div>
  </body>
</html>
```

### CSS ###

Ostatnią rzeczą o którą zadbamy w tej części będzie styl elementów. Dodaj do katalogu `stylesheets/` plik z materiałów.
Następnie w sekcji `head` dodaj wpis o arkuszach stylów, a następnie dodaj wyświetlanym elementom odpowiednie kalsy:


```html
<!--main.html-->
<html>
  <head>
    <title>Ćwirkacz</title>
    <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.5.8/angular.min.js"></script>
    <script src="javascripts/cwierkaczApp.js"></script>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css">
    <link rel="stylesheet" href="stylesheets/style.css">
  </head>
  <body ng-app="cwierkaczApp">
    <div id='main' class="container" ng-controller="mainController">
      <div class="col-md-offset-2 col-md-8">
        <div class="clearfix">
          <form ng-Submit="post()">
            <input required type="text" class="form-control" placeholder="Your name" ng-model="newPost.created_by" />
            <textarea required class="form-control" maxlength="200" rows="3" placeholder="Say something" ng-model="newPost.text"></textarea>
            <input class="btn submit-btn pull-right" type="submit" value="Ćwirk!" />
          </form>
          <div id="post-stream">
            <h4>>Ostatnie Ćwierki</h4>
                <div class="post" ng-repeat="post in posts | orderBy:'created_at':true" ng-class-odd="'odd'" ng-class-even="'even'">
                  <p>{{post.text}}</p>
                <small>Posted by @{{post.created_by}}</small>
                <small class="pull-right">{{post.created_at | date:"h:mma 'on' MMM d, y"}}</small>
                </div>
          </div>
        </div>
      </div>
    </div>
  </body>
</html>
```
