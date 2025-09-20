create database CEMS;
use CEMS;

-- CREATING USERS TABLE
create table users(user_id int primary key auto_increment, name varchar(50),role enum('student', 'teacher', 'admin'),
email varchar(50), password varchar(50), creation timestamp);

-- CREATING EVENTS TABLE
create table events(event_id int primary key auto_increment, title varchar(100), description text, 
organizer_id int, event_date date, capacity int, foreign key(organizer_id) references users(user_id));

-- CREATING REGISTRATIONS TABLE
create table registrations(reg_id int primary key auto_increment, event_id int, student_id int, status enum('registered','attended','cancelled'),
foreign key(event_id) references events(event_id),
foreign key(student_id) references users(user_id));

--  CREATING FEEDBACK TABLE
create table feedback(feedback_id int primary key auto_increment, event_id int, student_id int, rating int, comments text,
foreign key (event_id) references events(event_id),
foreign key(student_id) references users(user_id));
