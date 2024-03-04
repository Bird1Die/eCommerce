
-- database already exists

\c :dbname 

CREATE DOMAIN  String4VarName AS VARCHAR(30) ;
CREATE DOMAIN  String4Info as VARCHAR(200) ;

CREATE domain Password as varchar(30);

--CREATE DOMAIN DomainEmail AS VARCHAR(255)
  --CHECK (VALUE ~* '^[A-Za-z0-9._%+-]+@example\.com$');

--CREATE DOMAIN DomainPhone AS VARCHAR(20)
  --CHECK (VALUE ~ '^(\+\d{1,3}\s?)?(\(\d{1,4}\)|\d{1,4})[-.\s]?\d{1,10}[-.\s]?\d{1,10}$');

CREATE DOMAIN DomainCap AS VARCHAR(5);

CREATE TYPE DomainStatus AS ENUM ('available', 'unavailable');

CREATE TYPE ShippingStatus AS ENUM ('pendant', 'delivering', 'delivered');

CREATE TABLE IF NOT EXISTS ShippingAddress (
        id serial PRIMARY KEY,
        address String4Info NOT NULL,
        house_number String4Info NOT NULL,
        CAP DomainCap NOT NULL,
        entryphone String4Info NOT NULL,
        note String4Info
);

CREATE TABLE IF NOT EXISTS CreditCard (
        id serial PRIMARY KEY,
        number char(16) NOT NULL,
        name String4Info NOT NULL,
        expiration_date VARCHAR(5) NOT NULL,
        cvc char(3) NOT NULL
);

CREATE TABLE IF NOT EXISTS Customer (
        id serial PRIMARY KEY,
        username String4VarName NOT NULL,
        password Password NOT NULL, 
        email String4Info NOT NULL,
        phone String4Info NOT NULL,
        shipping_address INTEGER REFERENCES ShippingAddress(id) ON DELETE SET NULL,
        creditCard INTEGER REFERENCES CreditCard(id) ON DELETE SET NULL, 
        iscrizione TIMESTAMP DEFAULT now()
);

CREATE TABLE IF NOT EXISTS Vendor (
        id serial PRIMARY KEY,
        username String4VarName UNIQUE NOT NULL,
        password Password NOT NULL, 
        email String4Info UNIQUE NOT NULL,
        phone String4Info NOT NULL
);


CREATE TABLE IF NOT EXISTS Insertion (
        id serial PRIMARY KEY,
        product String4Info,
        pr_description String4Info NOT NULL,
        price real NOT NULL,
        shipping_costs real NOT NULL,
        instant TIMESTAMP DEFAULT now(),
        insertion_status DomainStatus DEFAULT 'available',
        vendor INTEGER REFERENCES Vendor(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS orders (
        id serial PRIMARY KEY,
        product INTEGER REFERENCES Insertion(id) ON DELETE SET NULL,
        quantity INTEGER NOT NULL,
        customer INTEGER REFERENCES Customer(id) ON DELETE SET NULL,
        instant_date TIMESTAMP DEFAULT now()
);

CREATE TABLE IF NOT EXISTS Transporter (
        id serial PRIMARY KEY,
        name String4Info NOT NULL
);


CREATE TABLE IF NOT EXISTS Shipping (
        id serial PRIMARY KEY,
        number_order INTEGER REFERENCES orders(id) ON DELETE CASCADE,
        transporter INTEGER REFERENCES Transporter(id) ON DELETE SET NULL,
        shipping_status ShippingStatus DEFAULT 'pendant',
        delivered  TIMESTAMP
);





