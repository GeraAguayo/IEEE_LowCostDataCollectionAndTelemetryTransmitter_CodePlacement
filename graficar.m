% -------------------------------------------------------------------
% Script de Telemetría Rover - Formato IEEE (Grayscale, Dual Language, PNG)
% -------------------------------------------------------------------
clear; clc; close all;

% 1. Cargar y filtrar datos
filename = 'roadtrip_logic_computer.csv';
data = readtable(filename);

% Combinar fecha y hora
timeStrings = strcat(string(data.Date), {' '}, string(data.Time));
t = datetime(timeStrings, 'InputFormat', 'yyyy-MM-dd HH:mm:ss');

% FILTRO: Corte a las 11:57:30 para evitar el spike
limitTime = timeofday(datetime('11:57:30', 'InputFormat', 'HH:mm:ss'));
mask = timeofday(t) <= limitTime;
data = data(mask, :);
t = t(mask);

% 2. Configuración General
figWidthFull = 7.15; 
fontName = 'Times New Roman';
fontSizeBase = 8;
grayColor = [0.15 0.15 0.15]; 

% Definición de idiomas y etiquetas
languages = {'EN', 'ES'};

for l = 1:length(languages)
    lang = languages{l};
    
    if strcmp(lang, 'EN')
        lbls = {'Time', 'Altitude', 'Pressure', 'Temperature', 'Humidity', 'Gas', 'Latitude', 'Longitude', 'Distance'};
        mainTitles = {'Altitude and Pressure', 'Environmental Sensors', 'GPS and Distance'};
    else
        lbls = {'Tiempo', 'Altitud', 'Presión', 'Temperatura', 'Humedad', 'Gas', 'Latitud', 'Longitud', 'Distancia'};
        mainTitles = {'Altitud y Presión', 'Sensores Ambientales', 'GPS y Distancia'};
    end

    % -------------------------------------------------------------------
    % FIGURA 1: Altitud y Presión (1x2)
    % -------------------------------------------------------------------
    fig1 = figure('Units', 'inches', 'Position', [1, 1, figWidthFull, 3.5], 'Color', 'w', 'Visible', 'off');
    tl1 = tiledlayout(1, 2, 'TileSpacing', 'compact', 'Padding', 'compact');
    
    nexttile;
    plot_grayscale(t, data.Altitude, grayColor, [lbls{2}, ' (m)'], fontName, fontSizeBase);
    nexttile;
    plot_grayscale(t, data.Pressure, grayColor, [lbls{3}, ' (Pa)'], fontName, fontSizeBase);
    
    title(tl1, mainTitles{1}, 'FontName', fontName, 'FontWeight', 'bold');
    xlabel(tl1, [lbls{1}, ' (HH:mm)'], 'FontName', fontName);
    exportgraphics(fig1, ['Fig_Alt_Pres_', lang, '.png'], 'Resolution', 300);

    % -------------------------------------------------------------------
    % FIGURA 2: Temperatura, Humedad y Gas (1x3)
    % -------------------------------------------------------------------
    fig2 = figure('Units', 'inches', 'Position', [1, 1, figWidthFull, 3.2], 'Color', 'w', 'Visible', 'off');
    tl2 = tiledlayout(1, 3, 'TileSpacing', 'compact', 'Padding', 'compact');
    
    nexttile;
    plot_grayscale(t, data.Temperature, grayColor, [lbls{4}, ' (C^\circ)'], fontName, fontSizeBase);
    nexttile;
    plot_grayscale(t, data.Humidity, grayColor, [lbls{5}, ' (%)'], fontName, fontSizeBase);
    nexttile;
    plot_grayscale(t, data.Gas, grayColor, [lbls{6}, ' (Ohm)'], fontName, fontSizeBase);
    
    title(tl2, mainTitles{2}, 'FontName', fontName, 'FontWeight', 'bold');
    xlabel(tl2, [lbls{1}, ' (HH:mm)'], 'FontName', fontName);
    exportgraphics(fig2, ['Fig_Env_Sensors_', lang, '.png'], 'Resolution', 300);

    % -------------------------------------------------------------------
    % FIGURA 3: Latitud, Longitud y Distancia (1x3)
    % -------------------------------------------------------------------
    fig3 = figure('Units', 'inches', 'Position', [1, 1, figWidthFull, 3.2], 'Color', 'w', 'Visible', 'off');
    tl3 = tiledlayout(1, 3, 'TileSpacing', 'compact', 'Padding', 'compact');
    
    % Latitud
    nexttile;
    plot_grayscale(t, data.Latitude, grayColor, [lbls{7}, ' (deg)'], fontName, fontSizeBase);
    
    % Longitud
    nexttile;
    plot_grayscale(t, data.Longitude, grayColor, [lbls{8}, ' (deg)'], fontName, fontSizeBase);
    
    % Distancia Avanzada
    nexttile;
    % Se asume que la columna se llama 'DistanceTraveled' o similar
    try
        distData = data.DistanceTraveled;
    catch
        distData = data.Distance_Traveled; % Ajuste por si MATLAB cambió el nombre al importar
    end
    plot_grayscale(t, distData, grayColor, [lbls{9}, ' (km)'], fontName, fontSizeBase);
    
    title(tl3, mainTitles{3}, 'FontName', fontName, 'FontWeight', 'bold');
    xlabel(tl3, [lbls{1}, ' (HH:mm)'], 'FontName', fontName);
    exportgraphics(fig3, ['Fig_GPS_Distance_', lang, '.png'], 'Resolution', 300);
    
    close(fig1); close(fig2); close(fig3);
end

disp('Exportación exitosa: 6 imágenes PNG generadas (incluyendo distancia en GPS).');

function plot_grayscale(x, y, color, ylbl, fname, fsize)
    plot(x, y, 'LineWidth', 1.2, 'Color', color);
    grid on;
    ax = gca;
    ax.FontName = fname;
    ax.FontSize = fsize;
    ax.GridLineStyle = ':';
    ax.GridColor = [0.6 0.6 0.6]; 
    ax.Box = 'off';
    ylabel(ylbl);
    xtickformat('HH:mm');
    ax.XTickLabelRotation = 45; 
end