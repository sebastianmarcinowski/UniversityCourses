clc
close all 
clear all

u.okno = figure
set(u.okno)
set(u.okno,'name','Zadanie1','numbertitle','off','color',[0.1;0.2;0.3])
u.edycja =  uicontrol('Style','edit','Position',[175;200;200;50],'String','Podaj kolor')
u.guzik = uicontrol('Style','pushbutton','Position',[175;100;200;50],'String','OK','Callback',{@Lab2zad2_2,u})
set(u.edycja, 'Units', 'normalized')
set(u.guzik, 'Units', 'normalized')