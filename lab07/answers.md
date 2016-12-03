**Dlaczego wybranie tagu latest dla obrazu nie jest dobrym pomysłem?**
Dlatego, ze nie mamy pewności czy w następne wersje obrazu będą kompatybilne np. z bibliotekami z których korzystamy. Wybierając konkretną wersję dokładnie wiemy co będzie działać w naszym kontenerze i jak będzie działać.

**Na jakim obrazie bazuje kontener w przypadku budowania od zera?**

Podstawowym obrazem na którym można bazować budując obraz od zera jest obraz o nazwie `scratch`.
Budowanie na jego podstawie odbywa się w ten sposób:
```
FROM scratch
ADD hello /
CMD ["/hello"]
```

**Czy znasz jakieś inne środowisko które wykorzystuje podobny mechanizm? (.dockerignore)**

Tak, choćby git.
