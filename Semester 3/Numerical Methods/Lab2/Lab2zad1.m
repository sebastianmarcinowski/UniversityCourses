clc
close all 
clear all

u.okno = figure 
set(u.okno) %Uwaga – koniecznie bez średnika 
set(u.okno,'name','Zadanie1','numbertitle','off')
kolor = get(u.okno,'color')
%set(u.okno,'color',[0;0;0])
set(u.okno,'color',[0.12;0.10;0.23])
u.napis = uicontrol('Style','text','Position',[100;300;200;50],'String','DHL')
u.edycja = uicontrol('Style','edit','Position',[100;200;200;50],'String','...')
u.guzik = uicontrol('Style','pushbutton','Position',[100;100;200;50],'String','OK','Callback',{@Lab2zad1_funkcja,u})