# Kierunki rozwoju Oprogramowania #

## zapraszam na stronę http://dillinger.io/ 

## MEAN Stack ##

Wypakuj drugą paczkę dołączoną do laboratorium.
Zapoznaj się z plikiem package.json, zainstaluj wymagane zależności

Zapoznaj się z modelami dostępnymi w projekcie. Plik `models/models.js`
```javascript
post = new Post();
post.message = 'lalala';
post.save(function(err, post) {
  if (err){
    return res.send(500, err);
  }
  return res.json(post); // return res.send(200, post));
});
```

Zapoznaj się z plikiem `app.js`. Sczególnie zwróć uwagę na linijki 8-10 oraz 23-25. Jest to przykład wczytywania modułów. jeżeli jesteś ciekawy w jaki sposób `Angular` wie co znajduje się w module, zobacz na ostatnią linijkę w każdym z dołączanych plików

Zapoznaj się z plikiem `public/javascript/cwierkaczApp.js`

Zapoznaj się z plikami `HTML` w folderze `public/` - są tam wygenerowane templaty (ale nie tylko)

Zapoznaj się z plikami w folderze `routes` (logika aplikacji po stronie serwera) i views (templaty dla silnika express). Zauważ, że pomimo wyświetlania zawartości strony głównej i odwołania do pliku `index.html`, taki plik nie istnieje.

## Zadania do zrealizowania

1. Popraw API
0. Popraw model (zdefiniuj pola username i password dla modelu `User`)
0. Dodaj połączenie z bazą danych (najpierw należy uruchomić demona `mongodb`: `mongod --dbpath /home/student/db`, może istnieć potrzeba stworzenia katalogu `/home/student/db`)
0. Popraw implementację akcji dodawania nowego posta
0. Zmień formatowanie daty w widoku
0. Popraw funkcje logowania i rejestracji. Skorzystaj z funkcji skrótu do tworzenia hashu hasła, możesz użyć do tego modułu `bcrypt`: 
  ```javascript
  var hash = bcrypt.hashSync("password");
  ```
0. Dodaj przycisk do usuwania wpisu (tylko danego użytkownika)
0. **zadanie dodatkowe** - trzymaj informację o użytkowniku w cookies (pomiędzy odświeżeniami strony), możesz też użyć dodatkowych modułów dedykowanych do uwieżytelniania
0. **zadanie dodatkowe** - zainstaluj jade i zmień templaty tak żeby wykorzystywały nowy silnik. Przeksztłć wszystkie na postać obsługiwaną przez nowy silnik