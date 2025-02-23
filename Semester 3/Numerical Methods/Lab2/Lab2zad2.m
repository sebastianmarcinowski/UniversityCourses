clc
clear all
close all

u.okno = figure
set(u.okno)
set(u.okno,'name','Zadanie1','numbertitle','off','color',[0.1;0.2;0.3])
%kolor = input('Wybierz kolor (niebieski,zielony lub czerwony): ');
u.edycja =  uicontrol('Style','edit','Position',[175;200;200;50],'String','Podaj kolor')
u.guzik = uicontrol('Style','pushbutton','Position',[175;100;200;50],'String','OK','Callback',{@Lab2zad2_funkcja,u})