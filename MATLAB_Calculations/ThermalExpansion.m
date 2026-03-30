function [dVC,dVF] = ThermalExpansion(alpha,dT,Vo,CorF)

% alpha = coefficient of heat transfer
% CorF = alpha in units Celsius or Fahrenheit
% dT = change in temperature of system (C)
% Vo = initial volume of system (m^3)
% dVC,dVF = change in volume of system (mm^3,in^3)

if CorF == 'F'      % coef given in mm_mC
    alpha_F = alpha;
    dT_F = dT;
    Vo_in3 = Vo;
else
    alpha_F = alpha * ((0.0393701 / 39.3701) * 9 / 5);
    dT_F = dT * 9 / 5 + 32;
    Vo_in3 = Vo * 61023.7;
    
end

dVF = 3 * alpha_F * dT_F * Vo_in3;
dVC = dVF * 16387.1;

fprintf('Expansion (alpha_F): %.4f in^3\n', dVF);
fprintf('Expansion (alpha_C): %.4f mm^3\n', dVC);

% ThermalExpansion(0.0001,45,567,'F');
% Variables : Starboard HDPE, 25-50C, 9x9x7in
%
%   Expansion (alpha_F): 7.6545 in^3
%   Expansion (alpha_C): 125435.0569 mm^3
%
% Percent of system expanded
%   567 / 7.6545 = 74.0741
%   1 / 74.0741 = 0.0135 * 100 = 1.35% from 25C > 50C

end
