/* Create Clients Table*/
CREATE TABLE clients (
    id_client INTEGER PRIMARY KEY AUTOINCREMENT,
    nom VARCHAR(30) NOT NULL,
    prenom VARCHAR(30) NOT NULL,
    age INT NOT NULL,
    adresse VARCHAR(50) NOT NULL,
    tel NUMBER(10) NOT NULL,

    CONSTRAINT const_age CHECK( age > 0 )
);

/*Create Accounts Table*/
CREATE TABLE comptes (
    id_compte INTEGER PRIMARY KEY AUTOINCREMENT,
    date_creation DATE NOT NULL,
    solde REAL NOT NULL,
    type VARCHAR(20) NOT NULL,
    id_client INT,

    CONSTRAINT fk_id_client FOREIGN KEY(id_client) REFERENCES clients(id_client),
    CONSTRAINT fk_solde CHECK( SOLDE > 0)
);

/*Create Transactions Table*/
CREATE TABLE transactions (
    id_transaction INTEGER PRIMARY KEY AUTOINCREMENT,
    date_transaction DATE NOT NULL,
    type_transaction VARCHAR(30) NOT NULL,
    montant REAL NOT NULL,

    /* numero de compte object de la transaction */
    id_source INTEGER NOT NULL,
    id_destination INTEGER,

    CONSTRAINT fk_id_source FOREIGN KEY(id_source) REFERENCES comptes(id_compte) ON DELETE CASCADE,
    CONSTRAINT fk_id_destination FOREIGN KEY(id_destination) REFERENCES comptes(id_compte) ON DELETE CASCADE
);