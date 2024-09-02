BAGISTER

Cilj projekta jeste razvoj malog automobila sa pogonom 4x4 u cilju razvijanja tehnologija upravljive, polu autonomne i autonomne voznje 

Oprema: 
        - Mikrokontroler Arduino Uno
        - Mikrokontroler ESP-32 WROM

        - Bloututh modul HC-06
        - Ultrasonicni senozori
        - Dzojstik
        - Motor drajver L986N

        Napajanje: 2 x 9V (Auto) 6V (Dzojstik)

Specifikacije Softvera:

    Komunikacija drajvera sasije i ostalih komponenata vrsi se putem 32-bitne koamnde
            0xAB 0x## 0x## 0x## 0x## 0xCD (Foward Back Left Right);
        Specijalne koamande:
            0x11 0x22 0x33 0x44 // dzojstik zahtjeva ponovno konektovanje
            0x04 0x04 0x04 0x04 // automobil salje potvrdu konektovanja
            0x01 0x23 0x45 0x67 // potvrda da je auto primilo komandu
            0x0F 0x0F 0x0F 0x0F //zahtjev automobila za restartovanje komunikacije 
            

    __chassis.h__
        Sluzi za osnovnu kontrolu motora na automobilu  te upravljanje samom sasijom
        omogucava pojedinacno startovanje motora ali i pokretanje kompletne sasije
        Promjenu brzine motora bez zaustavljanja, zaustavljanje samog vozila
        Omogucava i start auta napjed i nazad uz najbolju kombinaciju startovanja motora
        Za kontrolu motora oslanja se na dva drajvera L986N
    __carDrive.h__
        Omogucava sledeci nivo kontrole nad autom nadogradjujuci se chassis.h koju i 
        ova biblioteka koristi
        Daje mogucnost naprednijeg i stabilnijeg upravljanja vozilom
        Daje gotove komande za veci broj funkcionalnosti (rotiranje u mjestu, skretanje u voznji)
        Smanjuje nivo stvari o kojima brine krajnji korisnik i stabilizuje upravnjanje
        Svojevrsna nadogradnja chassis.h jer je koristi u potpunosti za pristup motorima
        Omogucava i napredniji sistem kontrole putem komandi koje mogu davati drugi moduli sistema 
        Omogucava citanje koamndi i upravljanje vozilom na osnovu datih koamandi u formatu 0x########
        

Istorija verzija:

    -v1.0:

    -v1.1:
        -omogucen prijem podataka putem Bloututh veze
        - implementiran privremeni sistem ocitavanja dolaznih podataka i kontrole na sonovu njih

    -v1.1.2
        -ispravljen bag kod nemogucnosti da se dvije koamnde izvrse jedna za drugom poslje zaustavljanja
        bag je bio u tome jer je falilo menjanje stanja motora u kacije stopCar u zaustavljeno
        sto je rezultovalo time da se ne pokrenutim motorima ustvari probala mjenjati brzina
    -V1.2
        -Dodat fajl joystick.cpp sa kodom za dzojstik implementiran na ESP-32 platformi
    -v1.3
        -Obezbjedjivanje komunikacije putem sistema kojim se unosi oznaka za pocetak i kraj komunikacije
        ovim se izbjegava da slucajno poslati ili neki ne poslati bit narusi kompletnu komunikaciju sto se
        nerjetko desavalo i uvjek pri paljenju i gasenju zdojstika
    -v1.4
        -Unapredjena komunikacija auto - dyojstik koja je sada two-way 
        Ostvaruje se putem slanja komandi izmedju uredjaja 
        uvedena je poruka potvrde koju auto salje kada uspjesno primi komandu
        -postoji sistem na autu koji je u stanju da detektuje gubitak konekcije
        nakon cega se prelazi u rezim ponovnog povezivanja ali i sistem kojim se 
        po potrebi dzojstiku salje signal za rekonektovanje.
        Dzojstik takodje moze biti u dva stanja a to su povezivanje ili redovni  rezim rada
