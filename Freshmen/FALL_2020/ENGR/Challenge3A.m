BEAM = {'Steel', 5, 11.8;
        'Titanium' , 7, 13.1;
        'Copper', 9, 12.5};

mett_option = BEAM{:,1};

Choice = menu('METAL', Choice);

melt_name = BEAM(Choice,1);

defL = input("Enter deflection, < 4 inches[1]");