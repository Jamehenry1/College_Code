G = {'Earth','Mar','Venus'; 9.81,3.71,8.87};
Planets = G(1,:);
Planet_num = menu('Planet Pick', Planets);
g = G{2,Planet_num};