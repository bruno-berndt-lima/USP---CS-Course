-- Copyright (C) 1991-2014 Altera Corporation. All rights reserved.
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, the Altera Quartus II License Agreement,
-- the Altera MegaCore Function License Agreement, or other 
-- applicable license agreement, including, without limitation, 
-- that your use is for the sole purpose of programming logic 
-- devices manufactured by Altera and sold by Altera or its 
-- authorized distributors.  Please refer to the applicable 
-- agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 64-Bit"
-- VERSION "Version 14.0.0 Build 200 06/17/2014 SJ Web Edition"

-- DATE "06/16/2021 01:05:07"

-- 
-- Device: Altera 5CEBA4F23C7 Package FBGA484
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY ALTERA_LNSIM;
LIBRARY CYCLONEV;
LIBRARY IEEE;
USE ALTERA_LNSIM.ALTERA_LNSIM_COMPONENTS.ALL;
USE CYCLONEV.CYCLONEV_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	\proj-aula05-uso-do-quartus\ IS
    PORT (
	a : OUT std_logic;
	b0 : IN std_logic;
	b3 : IN std_logic;
	b1 : IN std_logic;
	b2 : IN std_logic;
	b : OUT std_logic;
	c : OUT std_logic;
	d : OUT std_logic;
	e : OUT std_logic;
	f : OUT std_logic;
	g : OUT std_logic
	);
END \proj-aula05-uso-do-quartus\;

-- Design Ports Information
-- a	=>  Location: PIN_U21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b	=>  Location: PIN_V21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- c	=>  Location: PIN_W22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- d	=>  Location: PIN_W21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- e	=>  Location: PIN_Y22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- f	=>  Location: PIN_Y21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- g	=>  Location: PIN_AA22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b1	=>  Location: PIN_V13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b2	=>  Location: PIN_T13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b0	=>  Location: PIN_U13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b3	=>  Location: PIN_T12,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF \proj-aula05-uso-do-quartus\ IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_a : std_logic;
SIGNAL ww_b0 : std_logic;
SIGNAL ww_b3 : std_logic;
SIGNAL ww_b1 : std_logic;
SIGNAL ww_b2 : std_logic;
SIGNAL ww_b : std_logic;
SIGNAL ww_c : std_logic;
SIGNAL ww_d : std_logic;
SIGNAL ww_e : std_logic;
SIGNAL ww_f : std_logic;
SIGNAL ww_g : std_logic;
SIGNAL \~QUARTUS_CREATED_GND~I_combout\ : std_logic;
SIGNAL \b2~input_o\ : std_logic;
SIGNAL \b0~input_o\ : std_logic;
SIGNAL \b1~input_o\ : std_logic;
SIGNAL \b3~input_o\ : std_logic;
SIGNAL \inst4~combout\ : std_logic;
SIGNAL \inst11~combout\ : std_logic;
SIGNAL \inst22~0_combout\ : std_logic;
SIGNAL \inst32~combout\ : std_logic;
SIGNAL \inst41~0_combout\ : std_logic;
SIGNAL \inst46~0_combout\ : std_logic;
SIGNAL \inst64~combout\ : std_logic;
SIGNAL \ALT_INV_b3~input_o\ : std_logic;
SIGNAL \ALT_INV_b0~input_o\ : std_logic;
SIGNAL \ALT_INV_b2~input_o\ : std_logic;
SIGNAL \ALT_INV_b1~input_o\ : std_logic;

BEGIN

a <= ww_a;
ww_b0 <= b0;
ww_b3 <= b3;
ww_b1 <= b1;
ww_b2 <= b2;
b <= ww_b;
c <= ww_c;
d <= ww_d;
e <= ww_e;
f <= ww_f;
g <= ww_g;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
\ALT_INV_b3~input_o\ <= NOT \b3~input_o\;
\ALT_INV_b0~input_o\ <= NOT \b0~input_o\;
\ALT_INV_b2~input_o\ <= NOT \b2~input_o\;
\ALT_INV_b1~input_o\ <= NOT \b1~input_o\;

-- Location: IOOBUF_X52_Y0_N53
\a~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst4~combout\,
	devoe => ww_devoe,
	o => ww_a);

-- Location: IOOBUF_X51_Y0_N36
\b~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst11~combout\,
	devoe => ww_devoe,
	o => ww_b);

-- Location: IOOBUF_X48_Y0_N76
\c~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst22~0_combout\,
	devoe => ww_devoe,
	o => ww_c);

-- Location: IOOBUF_X50_Y0_N36
\d~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst32~combout\,
	devoe => ww_devoe,
	o => ww_d);

-- Location: IOOBUF_X48_Y0_N93
\e~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst41~0_combout\,
	devoe => ww_devoe,
	o => ww_e);

-- Location: IOOBUF_X50_Y0_N53
\f~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst46~0_combout\,
	devoe => ww_devoe,
	o => ww_f);

-- Location: IOOBUF_X46_Y0_N36
\g~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst64~combout\,
	devoe => ww_devoe,
	o => ww_g);

-- Location: IOIBUF_X34_Y0_N1
\b2~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b2,
	o => \b2~input_o\);

-- Location: IOIBUF_X33_Y0_N41
\b0~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b0,
	o => \b0~input_o\);

-- Location: IOIBUF_X33_Y0_N58
\b1~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b1,
	o => \b1~input_o\);

-- Location: IOIBUF_X34_Y0_N18
\b3~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_b3,
	o => \b3~input_o\);

-- Location: MLABCELL_X45_Y1_N30
inst4 : cyclonev_lcell_comb
-- Equation(s):
-- \inst4~combout\ = ( \b3~input_o\ & ( (\b0~input_o\ & (!\b2~input_o\ $ (!\b1~input_o\))) ) ) # ( !\b3~input_o\ & ( (!\b1~input_o\ & (!\b2~input_o\ $ (!\b0~input_o\))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0110000001100000011000000110000000010010000100100001001000010010",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_b2~input_o\,
	datab => \ALT_INV_b0~input_o\,
	datac => \ALT_INV_b1~input_o\,
	dataf => \ALT_INV_b3~input_o\,
	combout => \inst4~combout\);

-- Location: MLABCELL_X45_Y1_N33
inst11 : cyclonev_lcell_comb
-- Equation(s):
-- \inst11~combout\ = ( \b3~input_o\ & ( (!\b0~input_o\ & (\b2~input_o\)) # (\b0~input_o\ & ((\b1~input_o\))) ) ) # ( !\b3~input_o\ & ( (\b2~input_o\ & (!\b0~input_o\ $ (!\b1~input_o\))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0001000101000100000100010100010001000100011101110100010001110111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_b2~input_o\,
	datab => \ALT_INV_b0~input_o\,
	datad => \ALT_INV_b1~input_o\,
	dataf => \ALT_INV_b3~input_o\,
	combout => \inst11~combout\);

-- Location: MLABCELL_X45_Y1_N36
\inst22~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst22~0_combout\ = ( \b3~input_o\ & ( (\b2~input_o\ & ((!\b0~input_o\) # (\b1~input_o\))) ) ) # ( !\b3~input_o\ & ( (!\b0~input_o\ & (!\b2~input_o\ & \b1~input_o\)) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000011000000000000001100000000001100000011110000110000001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \ALT_INV_b0~input_o\,
	datac => \ALT_INV_b2~input_o\,
	datad => \ALT_INV_b1~input_o\,
	dataf => \ALT_INV_b3~input_o\,
	combout => \inst22~0_combout\);

-- Location: MLABCELL_X45_Y1_N39
inst32 : cyclonev_lcell_comb
-- Equation(s):
-- \inst32~combout\ = ( \b3~input_o\ & ( (\b1~input_o\ & (!\b2~input_o\ $ (\b0~input_o\))) ) ) # ( !\b3~input_o\ & ( (!\b2~input_o\ & (\b0~input_o\ & !\b1~input_o\)) # (\b2~input_o\ & (!\b0~input_o\ $ (\b1~input_o\))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0110011000010001011001100001000100000000100110010000000010011001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_b2~input_o\,
	datab => \ALT_INV_b0~input_o\,
	datad => \ALT_INV_b1~input_o\,
	dataf => \ALT_INV_b3~input_o\,
	combout => \inst32~combout\);

-- Location: MLABCELL_X45_Y1_N42
\inst41~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst41~0_combout\ = ( \b3~input_o\ & ( (\b0~input_o\ & (!\b2~input_o\ & !\b1~input_o\)) ) ) # ( !\b3~input_o\ & ( ((\b2~input_o\ & !\b1~input_o\)) # (\b0~input_o\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0011111100110011001111110011001100110000000000000011000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \ALT_INV_b0~input_o\,
	datac => \ALT_INV_b2~input_o\,
	datad => \ALT_INV_b1~input_o\,
	dataf => \ALT_INV_b3~input_o\,
	combout => \inst41~0_combout\);

-- Location: MLABCELL_X45_Y1_N45
\inst46~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst46~0_combout\ = ( \b3~input_o\ & ( (\b2~input_o\ & (\b0~input_o\ & !\b1~input_o\)) ) ) # ( !\b3~input_o\ & ( (!\b2~input_o\ & ((\b1~input_o\) # (\b0~input_o\))) # (\b2~input_o\ & (\b0~input_o\ & \b1~input_o\)) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0010001010111011001000101011101100010001000000000001000100000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_b2~input_o\,
	datab => \ALT_INV_b0~input_o\,
	datad => \ALT_INV_b1~input_o\,
	dataf => \ALT_INV_b3~input_o\,
	combout => \inst46~0_combout\);

-- Location: MLABCELL_X45_Y1_N48
inst64 : cyclonev_lcell_comb
-- Equation(s):
-- \inst64~combout\ = ( !\b0~input_o\ & ( \b3~input_o\ & ( (\b2~input_o\ & !\b1~input_o\) ) ) ) # ( \b0~input_o\ & ( !\b3~input_o\ & ( !\b2~input_o\ $ (\b1~input_o\) ) ) ) # ( !\b0~input_o\ & ( !\b3~input_o\ & ( (!\b2~input_o\ & !\b1~input_o\) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1010000010100000101001011010010101010000010100000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_b2~input_o\,
	datac => \ALT_INV_b1~input_o\,
	datae => \ALT_INV_b0~input_o\,
	dataf => \ALT_INV_b3~input_o\,
	combout => \inst64~combout\);

-- Location: LABCELL_X20_Y23_N0
\~QUARTUS_CREATED_GND~I\ : cyclonev_lcell_comb
-- Equation(s):

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
;
END structure;


