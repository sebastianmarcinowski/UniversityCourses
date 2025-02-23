function[]=Lab2zad2_2(h,~,u)
kolor = get(u.edycja,'string');
w = str2num(kolor);
% set(u.okno,'color',kolor)
if(isnumeric(str2double(kolor))==true)
    if (length(w)==3)
        if(0<=w(1) && w(1)<=1) && (0<=w(2) && w(2)<=1) && (0<=w(3)&&w(3)<=1)
            set(u.okno,'color',kolor)
        end
    else
        switch kolor
            case 'zielony'
                set(u.okno,'color','green')
            case 'czerwony'
                set(u.okno,'color','red')
            case 'niebieski'
                set(u.okno,'color','blue')
            otherwise
                set(u.okno,'color','white')
        end
    end
end