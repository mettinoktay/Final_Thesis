       r = 1;          %diameter of rotor
  lambda = 3;          %tip speed ratio
       R = [0:0.05:1]; %local radius to radius rati
lambda_r = lambda*R;   %local tip speed ratio
       B = 5;          %blade count
      Cl = 1.08;       %lift coefficient
     psi = 38.1972.*atan(1./lambda_r);
       c = ((25.1327.*R)/(B*Cl).*(1-cos(psi*pi/180)))*r;
plot(R, psi)
xlabel('Nondimensionalized radius')
ylabel('Twist angle')
title('Twist angle distribution')
figure
plot(R, c)
xlabel('Nondimensionalized radius')
ylabel('Chord length')
title('Chord length distribution')