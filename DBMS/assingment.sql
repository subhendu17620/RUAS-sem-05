-- creating database
create database online_furniture_store;

-- using database
use online_furniture_store;

-- creating table customer
create table customer(
    name varchar(20),
    email varchar(20) UNIQUE,
    password varchar(20) NOT NULL,
    address varchar(200) NOT NULL,
    user_id int NOT NULL PRIMARY KEY,
    phone_no int NOT NULL UNIQUE
);


-- creating table product
create table product(
    name varchar(20) NOT NULL,
    material  varchar(20),
    color  varchar(20),
    product_id int NOT NULL PRIMARY KEY,
    price int NOT NULL,
    inventory int NOT NULL
);

-- creating table category
create table category(
category_id int NOT NULL PRIMARY KEY,
category_title char(20) NOT NULL UNIQUE
);

-- creating table admin
create table admin(
    email varchar(20) UNIQUE,
    password varchar(20) NOT NULL,
    admin_id int  NOT NULL PRIMARY KEY
);

-- creating table payments
create table payments(
    payment_id int NOT NULL PRIMARY KEY ,
    user_id int  NOT NULL,
    FOREIGN KEY (user_id) REFERENCES customer(user_id)
);

-- creating table cart
create table cart(
    quantity int NOT NULL,
    product_id int  NOT NULL UNIQUE,
    user_id int  NOT NULL,
    payment_id int NOT NULL,
    FOREIGN KEY (payment_id) REFERENCES payments(payment_id),
    FOREIGN KEY (product_id) REFERENCES product(product_id),
    FOREIGN KEY (user_id) REFERENCES customer(user_id)
);

-- creating table buys
create table buys(
    product_id int  NOT NULL,
    user_id int  NOT NULL,
    payment_id int NOT NULL UNIQUE,
    FOREIGN KEY (product_id) REFERENCES product(product_id),
    FOREIGN KEY (user_id) REFERENCES customer(user_id),
    FOREIGN KEY (payment_id) REFERENCES payments(payment_id)
);


-- creating table category_contains
create table category_contains(
    product_id int  NOT NULL,
    category_id int  NOT NULL,
    FOREIGN KEY (product_id) REFERENCES product(product_id),
    FOREIGN KEY (category_id) REFERENCES category(category_id)
    );


-- creating table manages_category
create table manages_category(
    admin_id int  NOT NULL,
    category_id int  NOT NULL,
    FOREIGN KEY (admin_id) REFERENCES admin(admin_id),
    FOREIGN KEY (category_id) REFERENCES category(category_id)
);


-- creating table manages_product
create table manages_product(
    admin_id int  NOT NULL,
    product_id int  NOT NULL,
    FOREIGN KEY (admin_id) REFERENCES admin(admin_id),
    FOREIGN KEY (product_id) REFERENCES product(product_id)
);




-- inserting dummy data in the tables
insert into customer values('subhendu','s@gmail.com','subh@pass','delhi',1,987654);
insert into customer values('kenny','k@gmail.com','kenn@pass','punjab',2,789456);
insert into customer values('rohit','r@gmail.com','rohi@pass','bangalore',3,987564);


insert into product values('chair1','wood','brown',100, 1500,50);
insert into product values('chair2','plastic','red',101, 700,120);
insert into product values('table1','wood','black',200, 2000,70);
insert into product values('table2','plastic','orange',201, 1600,86);

insert into category values(1001,'chairs');
insert into category values(1002,'tables');

insert into admin values('a1@gmail.com','a1@pass',10001);
insert into admin values('a2@gmail.com','a2@pass',10002);

insert into payments values(501,1);
insert into payments values(502,2);
insert into payments values(503,3);
insert into payments values(504,1);

insert into cart values(5,100,1,501);
insert into cart values(8,201,1,501);

insert into buys values(100,2,502);
insert into buys values(101,1,504);

insert into category_contains values(100,1001);
insert into category_contains values(200,1002);

insert into manages_category values(10001,1001);
insert into manages_category values(10002,1002);

insert into manages_product values(10001,100); 
insert into manages_product values(10002,200); 



-- Update operations violating the schema constraints

update customer set phone_no='adm' where user_id=1; -- domain constraint
update customer set password=NULL where user_id=1; -- entity integrity constraint
update customer set user_id=1 where name='kenny'; -- key constraint

update product set price='abcd' where product_id=200; -- domain constraint
update product set price=NULL where product_id=200; -- entity integrity constraint
update product set product_id=101 where name='chair1'; -- key constraint

update category set category_id='jai' where category_title='chairs'; -- domain constraint
update category set category_id=NULL where category_title='tables'; -- entity integrity constraint
update category set category_id=1001 where category_title='tables'; -- key constraint

update payments set payment_id='abc' where user_id=1;  -- domain constraint
update payments set payment_id=NULL where user_id=1; -- entity integrity constraint
update payments set user_id=5 where payment_id=502; -- relational integrity  constraint





select * from customer;

-- desc customer;









