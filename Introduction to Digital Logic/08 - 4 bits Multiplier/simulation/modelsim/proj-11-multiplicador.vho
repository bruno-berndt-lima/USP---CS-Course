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

-- DATE "08/01/2021 03:25:55"

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

ENTITY 	\proj-11-multiplicador\ IS
    PORT (
	P0 : OUT std_logic;
	A0 : IN std_logic;
	B0 : IN std_logic;
	P1 : OUT std_logic;
	A1 : IN std_logic;
	B1 : IN std_logic;
	P2 : OUT std_logic;
	A2 : IN std_logic;
	B2 : IN std_logic;
	P3 : OUT std_logic;
	A3 : IN std_logic;
	B3 : IN std_logic;
	P4 : OUT std_logic;
	P5 : OUT std_logic;
	P6 : OUT std_logic;
	P7 : OUT std_logic
	);
END \proj-11-multiplicador\;

-- Design Ports Information
-- P0	=>  Location: PIN_AA2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- P1	=>  Location: PIN_AA1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- P2	=>  Location: PIN_W2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- P3	=>  Location: PIN_Y3,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- P4	=>  Location: PIN_N2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- P5	=>  Location: PIN_N1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- P6	=>  Location: PIN_U2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- P7	=>  Location: PIN_U1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A0	=>  Location: PIN_U13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B0	=>  Location: PIN_AA15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B1	=>  Location: PIN_AB15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A1	=>  Location: PIN_V13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B2	=>  Location: PIN_AA14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A2	=>  Location: PIN_T13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B3	=>  Location: PIN_AA13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A3	=>  Location: PIN_T12,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF \proj-11-multiplicador\ IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_P0 : std_logic;
SIGNAL ww_A0 : std_logic;
SIGNAL ww_B0 : std_logic;
SIGNAL ww_P1 : std_logic;
SIGNAL ww_A1 : std_logic;
SIGNAL ww_B1 : std_logic;
SIGNAL ww_P2 : std_logic;
SIGNAL ww_A2 : std_logic;
SIGNAL ww_B2 : std_logic;
SIGNAL ww_P3 : std_logic;
SIGNAL ww_A3 : std_logic;
SIGNAL ww_B3 : std_logic;
SIGNAL ww_P4 : std_logic;
SIGNAL ww_P5 : std_logic;
SIGNAL ww_P6 : std_logic;
SIGNAL ww_P7 : std_logic;
SIGNAL \~QUARTUS_CREATED_GND~I_combout\ : std_logic;
SIGNAL \A0~input_o\ : std_logic;
SIGNAL \B0~input_o\ : std_logic;
SIGNAL \inst|inst2~combout\ : std_logic;
SIGNAL \A1~input_o\ : std_logic;
SIGNAL \B1~input_o\ : std_logic;
SIGNAL \inst15|inst|inst~combout\ : std_logic;
SIGNAL \B2~input_o\ : std_logic;
SIGNAL \A2~input_o\ : std_logic;
SIGNAL \inst11|inst|inst1~combout\ : std_logic;
SIGNAL \inst4|inst|inst~combout\ : std_logic;
SIGNAL \B3~input_o\ : std_logic;
SIGNAL \A3~input_o\ : std_logic;
SIGNAL \inst10|inst|inst1~combout\ : std_logic;
SIGNAL \inst9|inst|inst~combout\ : std_logic;
SIGNAL \inst9|inst|inst4~combout\ : std_logic;
SIGNAL \inst5|inst2~combout\ : std_logic;
SIGNAL \inst8|inst|inst1~combout\ : std_logic;
SIGNAL \inst4|inst|inst4~combout\ : std_logic;
SIGNAL \inst6|inst|inst1~combout\ : std_logic;
SIGNAL \inst5|inst|inst1~combout\ : std_logic;
SIGNAL \inst3|inst2~combout\ : std_logic;
SIGNAL \inst10|inst|inst3~0_combout\ : std_logic;
SIGNAL \inst2|inst|inst1~0_combout\ : std_logic;
SIGNAL \inst6|inst|inst3~0_combout\ : std_logic;
SIGNAL \inst3|inst|inst1~combout\ : std_logic;
SIGNAL \inst2|inst|inst1~combout\ : std_logic;
SIGNAL \inst2|inst|inst3~0_combout\ : std_logic;
SIGNAL \inst5|inst|inst3~0_combout\ : std_logic;
SIGNAL \inst7|inst|inst1~combout\ : std_logic;
SIGNAL \inst7|inst|inst3~0_combout\ : std_logic;
SIGNAL \ALT_INV_A3~input_o\ : std_logic;
SIGNAL \ALT_INV_B3~input_o\ : std_logic;
SIGNAL \ALT_INV_A2~input_o\ : std_logic;
SIGNAL \ALT_INV_B2~input_o\ : std_logic;
SIGNAL \ALT_INV_A1~input_o\ : std_logic;
SIGNAL \ALT_INV_B1~input_o\ : std_logic;
SIGNAL \ALT_INV_B0~input_o\ : std_logic;
SIGNAL \ALT_INV_A0~input_o\ : std_logic;
SIGNAL \inst2|inst|ALT_INV_inst3~0_combout\ : std_logic;
SIGNAL \inst2|inst|ALT_INV_inst1~combout\ : std_logic;
SIGNAL \inst5|inst|ALT_INV_inst3~0_combout\ : std_logic;
SIGNAL \inst2|inst|ALT_INV_inst1~0_combout\ : std_logic;
SIGNAL \inst10|inst|ALT_INV_inst3~0_combout\ : std_logic;
SIGNAL \inst6|inst|ALT_INV_inst3~0_combout\ : std_logic;
SIGNAL \inst3|ALT_INV_inst2~combout\ : std_logic;
SIGNAL \inst6|inst|ALT_INV_inst1~combout\ : std_logic;
SIGNAL \inst8|inst|ALT_INV_inst1~combout\ : std_logic;
SIGNAL \inst4|inst|ALT_INV_inst4~combout\ : std_logic;
SIGNAL \inst5|ALT_INV_inst2~combout\ : std_logic;
SIGNAL \inst9|inst|ALT_INV_inst4~combout\ : std_logic;
SIGNAL \inst10|inst|ALT_INV_inst1~combout\ : std_logic;
SIGNAL \inst11|inst|ALT_INV_inst1~combout\ : std_logic;

BEGIN

P0 <= ww_P0;
ww_A0 <= A0;
ww_B0 <= B0;
P1 <= ww_P1;
ww_A1 <= A1;
ww_B1 <= B1;
P2 <= ww_P2;
ww_A2 <= A2;
ww_B2 <= B2;
P3 <= ww_P3;
ww_A3 <= A3;
ww_B3 <= B3;
P4 <= ww_P4;
P5 <= ww_P5;
P6 <= ww_P6;
P7 <= ww_P7;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
\ALT_INV_A3~input_o\ <= NOT \A3~input_o\;
\ALT_INV_B3~input_o\ <= NOT \B3~input_o\;
\ALT_INV_A2~input_o\ <= NOT \A2~input_o\;
\ALT_INV_B2~input_o\ <= NOT \B2~input_o\;
\ALT_INV_A1~input_o\ <= NOT \A1~input_o\;
\ALT_INV_B1~input_o\ <= NOT \B1~input_o\;
\ALT_INV_B0~input_o\ <= NOT \B0~input_o\;
\ALT_INV_A0~input_o\ <= NOT \A0~input_o\;
\inst2|inst|ALT_INV_inst3~0_combout\ <= NOT \inst2|inst|inst3~0_combout\;
\inst2|inst|ALT_INV_inst1~combout\ <= NOT \inst2|inst|inst1~combout\;
\inst5|inst|ALT_INV_inst3~0_combout\ <= NOT \inst5|inst|inst3~0_combout\;
\inst2|inst|ALT_INV_inst1~0_combout\ <= NOT \inst2|inst|inst1~0_combout\;
\inst10|inst|ALT_INV_inst3~0_combout\ <= NOT \inst10|inst|inst3~0_combout\;
\inst6|inst|ALT_INV_inst3~0_combout\ <= NOT \inst6|inst|inst3~0_combout\;
\inst3|ALT_INV_inst2~combout\ <= NOT \inst3|inst2~combout\;
\inst6|inst|ALT_INV_inst1~combout\ <= NOT \inst6|inst|inst1~combout\;
\inst8|inst|ALT_INV_inst1~combout\ <= NOT \inst8|inst|inst1~combout\;
\inst4|inst|ALT_INV_inst4~combout\ <= NOT \inst4|inst|inst4~combout\;
\inst5|ALT_INV_inst2~combout\ <= NOT \inst5|inst2~combout\;
\inst9|inst|ALT_INV_inst4~combout\ <= NOT \inst9|inst|inst4~combout\;
\inst10|inst|ALT_INV_inst1~combout\ <= NOT \inst10|inst|inst1~combout\;
\inst11|inst|ALT_INV_inst1~combout\ <= NOT \inst11|inst|inst1~combout\;

-- Location: IOOBUF_X0_Y18_N79
\P0~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|inst2~combout\,
	devoe => ww_devoe,
	o => ww_P0);

-- Location: IOOBUF_X0_Y18_N96
\P1~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst15|inst|inst~combout\,
	devoe => ww_devoe,
	o => ww_P1);

-- Location: IOOBUF_X0_Y18_N62
\P2~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst4|inst|inst~combout\,
	devoe => ww_devoe,
	o => ww_P2);

-- Location: IOOBUF_X0_Y18_N45
\P3~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst9|inst|inst~combout\,
	devoe => ww_devoe,
	o => ww_P3);

-- Location: IOOBUF_X0_Y19_N39
\P4~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst5|inst|inst1~combout\,
	devoe => ww_devoe,
	o => ww_P4);

-- Location: IOOBUF_X0_Y19_N56
\P5~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst3|inst|inst1~combout\,
	devoe => ww_devoe,
	o => ww_P5);

-- Location: IOOBUF_X0_Y19_N5
\P6~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst7|inst|inst1~combout\,
	devoe => ww_devoe,
	o => ww_P6);

-- Location: IOOBUF_X0_Y19_N22
\P7~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst7|inst|inst3~0_combout\,
	devoe => ww_devoe,
	o => ww_P7);

-- Location: IOIBUF_X33_Y0_N41
\A0~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A0,
	o => \A0~input_o\);

-- Location: IOIBUF_X36_Y0_N35
\B0~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B0,
	o => \B0~input_o\);

-- Location: LABCELL_X26_Y16_N0
\inst|inst2\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst|inst2~combout\ = (\A0~input_o\ & \B0~input_o\)

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000010100000101000001010000010100000101000001010000010100000101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_A0~input_o\,
	datac => \ALT_INV_B0~input_o\,
	combout => \inst|inst2~combout\);

-- Location: IOIBUF_X33_Y0_N58
\A1~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A1,
	o => \A1~input_o\);

-- Location: IOIBUF_X36_Y0_N52
\B1~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B1,
	o => \B1~input_o\);

-- Location: LABCELL_X26_Y16_N3
\inst15|inst|inst\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst15|inst|inst~combout\ = ( \B1~input_o\ & ( !\A0~input_o\ $ (((!\A1~input_o\) # (!\B0~input_o\))) ) ) # ( !\B1~input_o\ & ( (\A1~input_o\ & \B0~input_o\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000001111000000000000111101010101010110100101010101011010",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_A0~input_o\,
	datac => \ALT_INV_A1~input_o\,
	datad => \ALT_INV_B0~input_o\,
	dataf => \ALT_INV_B1~input_o\,
	combout => \inst15|inst|inst~combout\);

-- Location: IOIBUF_X34_Y0_N52
\B2~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B2,
	o => \B2~input_o\);

-- Location: IOIBUF_X34_Y0_N1
\A2~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A2,
	o => \A2~input_o\);

-- Location: LABCELL_X26_Y16_N6
\inst11|inst|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst11|inst|inst1~combout\ = ( \A0~input_o\ & ( (!\B0~input_o\ & (\B1~input_o\ & (\A1~input_o\))) # (\B0~input_o\ & (((\A2~input_o\)))) ) ) # ( !\A0~input_o\ & ( (!\B1~input_o\ & (((\B0~input_o\ & \A2~input_o\)))) # (\B1~input_o\ & (!\A1~input_o\ $ 
-- (((!\B0~input_o\) # (!\A2~input_o\))))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0001000100011110000100010001111000010000000111110001000000011111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B1~input_o\,
	datab => \ALT_INV_A1~input_o\,
	datac => \ALT_INV_B0~input_o\,
	datad => \ALT_INV_A2~input_o\,
	dataf => \ALT_INV_A0~input_o\,
	combout => \inst11|inst|inst1~combout\);

-- Location: LABCELL_X25_Y16_N0
\inst4|inst|inst\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst4|inst|inst~combout\ = !\inst11|inst|inst1~combout\ $ (((!\B2~input_o\) # (!\A0~input_o\)))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000111101011010000011110101101000001111010110100000111101011010",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B2~input_o\,
	datac => \inst11|inst|ALT_INV_inst1~combout\,
	datad => \ALT_INV_A0~input_o\,
	combout => \inst4|inst|inst~combout\);

-- Location: IOIBUF_X34_Y0_N35
\B3~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_B3,
	o => \B3~input_o\);

-- Location: IOIBUF_X34_Y0_N18
\A3~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_A3,
	o => \A3~input_o\);

-- Location: LABCELL_X26_Y16_N42
\inst10|inst|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst10|inst|inst1~combout\ = ( \B1~input_o\ & ( \A3~input_o\ & ( (!\B0~input_o\ & (((\A2~input_o\)))) # (\B0~input_o\ & ((!\A1~input_o\ & ((!\A2~input_o\))) # (\A1~input_o\ & ((!\A0~input_o\) # (\A2~input_o\))))) ) ) ) # ( !\B1~input_o\ & ( \A3~input_o\ 
-- & ( \B0~input_o\ ) ) ) # ( \B1~input_o\ & ( !\A3~input_o\ & ( (!\B0~input_o\ & (((\A2~input_o\)))) # (\B0~input_o\ & ((!\A1~input_o\ & ((\A2~input_o\))) # (\A1~input_o\ & (\A0~input_o\ & !\A2~input_o\)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000011110111001010101010101010101010010111011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B0~input_o\,
	datab => \ALT_INV_A1~input_o\,
	datac => \ALT_INV_A0~input_o\,
	datad => \ALT_INV_A2~input_o\,
	datae => \ALT_INV_B1~input_o\,
	dataf => \ALT_INV_A3~input_o\,
	combout => \inst10|inst|inst1~combout\);

-- Location: LABCELL_X26_Y16_N48
\inst9|inst|inst\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst9|inst|inst~combout\ = ( \inst10|inst|inst1~combout\ & ( \B2~input_o\ & ( !\A1~input_o\ $ (((\A0~input_o\ & (!\B3~input_o\ $ (!\inst11|inst|inst1~combout\))))) ) ) ) # ( !\inst10|inst|inst1~combout\ & ( \B2~input_o\ & ( !\A1~input_o\ $ 
-- (((!\A0~input_o\) # (!\B3~input_o\ $ (\inst11|inst|inst1~combout\)))) ) ) ) # ( \inst10|inst|inst1~combout\ & ( !\B2~input_o\ & ( (!\B3~input_o\) # (!\A0~input_o\) ) ) ) # ( !\inst10|inst|inst1~combout\ & ( !\B2~input_o\ & ( (\B3~input_o\ & \A0~input_o\) 
-- ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000010100000101111110101111101000110110001110011100100111000110",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B3~input_o\,
	datab => \ALT_INV_A1~input_o\,
	datac => \ALT_INV_A0~input_o\,
	datad => \inst11|inst|ALT_INV_inst1~combout\,
	datae => \inst10|inst|ALT_INV_inst1~combout\,
	dataf => \ALT_INV_B2~input_o\,
	combout => \inst9|inst|inst~combout\);

-- Location: LABCELL_X26_Y16_N54
\inst9|inst|inst4\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst9|inst|inst4~combout\ = ( \inst10|inst|inst1~combout\ & ( \B2~input_o\ & ( (\B3~input_o\ & (\A0~input_o\ & (!\A1~input_o\ $ (\inst11|inst|inst1~combout\)))) ) ) ) # ( !\inst10|inst|inst1~combout\ & ( \B2~input_o\ & ( (\B3~input_o\ & (\A0~input_o\ & 
-- (!\A1~input_o\ $ (!\inst11|inst|inst1~combout\)))) ) ) ) # ( \inst10|inst|inst1~combout\ & ( !\B2~input_o\ & ( (\B3~input_o\ & \A0~input_o\) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000001010000010100000001000001000000010000000001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B3~input_o\,
	datab => \ALT_INV_A1~input_o\,
	datac => \ALT_INV_A0~input_o\,
	datad => \inst11|inst|ALT_INV_inst1~combout\,
	datae => \inst10|inst|ALT_INV_inst1~combout\,
	dataf => \ALT_INV_B2~input_o\,
	combout => \inst9|inst|inst4~combout\);

-- Location: LABCELL_X25_Y16_N36
\inst5|inst2\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst5|inst2~combout\ = ( \A1~input_o\ & ( \B3~input_o\ ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000001111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datae => \ALT_INV_A1~input_o\,
	dataf => \ALT_INV_B3~input_o\,
	combout => \inst5|inst2~combout\);

-- Location: LABCELL_X26_Y16_N36
\inst8|inst|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst8|inst|inst1~combout\ = ( \B1~input_o\ & ( \A3~input_o\ & ( (!\B0~input_o\) # ((!\A2~input_o\ & ((!\A1~input_o\) # (!\A0~input_o\)))) ) ) ) # ( \B1~input_o\ & ( !\A3~input_o\ & ( (\B0~input_o\ & (\A1~input_o\ & \A2~input_o\)) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000001000100000000000000001111111010101010",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B0~input_o\,
	datab => \ALT_INV_A1~input_o\,
	datac => \ALT_INV_A0~input_o\,
	datad => \ALT_INV_A2~input_o\,
	datae => \ALT_INV_B1~input_o\,
	dataf => \ALT_INV_A3~input_o\,
	combout => \inst8|inst|inst1~combout\);

-- Location: LABCELL_X26_Y16_N30
\inst4|inst|inst4\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst4|inst|inst4~combout\ = ( \B0~input_o\ & ( \B1~input_o\ & ( (\B2~input_o\ & (\A0~input_o\ & \A2~input_o\)) ) ) ) # ( !\B0~input_o\ & ( \B1~input_o\ & ( (\B2~input_o\ & (\A1~input_o\ & \A0~input_o\)) ) ) ) # ( \B0~input_o\ & ( !\B1~input_o\ & ( 
-- (\B2~input_o\ & (\A0~input_o\ & \A2~input_o\)) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000010100000001000000010000000000000101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B2~input_o\,
	datab => \ALT_INV_A1~input_o\,
	datac => \ALT_INV_A0~input_o\,
	datad => \ALT_INV_A2~input_o\,
	datae => \ALT_INV_B0~input_o\,
	dataf => \ALT_INV_B1~input_o\,
	combout => \inst4|inst|inst4~combout\);

-- Location: LABCELL_X26_Y16_N12
\inst6|inst|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst6|inst|inst1~combout\ = ( \A2~input_o\ & ( \inst4|inst|inst4~combout\ & ( !\inst8|inst|inst1~combout\ $ (((!\B2~input_o\ & ((!\inst10|inst|inst1~combout\))) # (\B2~input_o\ & ((\inst10|inst|inst1~combout\) # (\A1~input_o\))))) ) ) ) # ( !\A2~input_o\ 
-- & ( \inst4|inst|inst4~combout\ & ( !\inst8|inst|inst1~combout\ $ (((!\inst10|inst|inst1~combout\ & ((!\B2~input_o\) # (!\A1~input_o\))))) ) ) ) # ( \A2~input_o\ & ( !\inst4|inst|inst4~combout\ & ( !\inst8|inst|inst1~combout\ $ (((!\B2~input_o\) # 
-- ((\A1~input_o\ & \inst10|inst|inst1~combout\)))) ) ) ) # ( !\A2~input_o\ & ( !\inst4|inst|inst4~combout\ & ( !\inst8|inst|inst1~combout\ $ (((!\B2~input_o\) # ((!\A1~input_o\) # (!\inst10|inst|inst1~combout\)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000111100011110010110100100101100011110111100000100101110100101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B2~input_o\,
	datab => \ALT_INV_A1~input_o\,
	datac => \inst8|inst|ALT_INV_inst1~combout\,
	datad => \inst10|inst|ALT_INV_inst1~combout\,
	datae => \ALT_INV_A2~input_o\,
	dataf => \inst4|inst|ALT_INV_inst4~combout\,
	combout => \inst6|inst|inst1~combout\);

-- Location: LABCELL_X25_Y16_N12
\inst5|inst|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst5|inst|inst1~combout\ = ( \inst6|inst|inst1~combout\ & ( !\inst9|inst|inst4~combout\ $ (\inst5|inst2~combout\) ) ) # ( !\inst6|inst|inst1~combout\ & ( !\inst9|inst|inst4~combout\ $ (!\inst5|inst2~combout\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0011110000111100001111000011110011000011110000111100001111000011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \inst9|inst|ALT_INV_inst4~combout\,
	datac => \inst5|ALT_INV_inst2~combout\,
	dataf => \inst6|inst|ALT_INV_inst1~combout\,
	combout => \inst5|inst|inst1~combout\);

-- Location: LABCELL_X25_Y16_N15
\inst3|inst2\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst3|inst2~combout\ = ( \B3~input_o\ & ( \A2~input_o\ ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000001111000011110000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \ALT_INV_A2~input_o\,
	dataf => \ALT_INV_B3~input_o\,
	combout => \inst3|inst2~combout\);

-- Location: LABCELL_X26_Y16_N24
\inst10|inst|inst3~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst10|inst|inst3~0_combout\ = ( \B1~input_o\ & ( \A3~input_o\ & ( (\B0~input_o\ & (((\A1~input_o\ & \A0~input_o\)) # (\A2~input_o\))) ) ) ) # ( \B1~input_o\ & ( !\A3~input_o\ & ( (\B0~input_o\ & (\A1~input_o\ & \A2~input_o\)) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000001000100000000000000000000000101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B0~input_o\,
	datab => \ALT_INV_A1~input_o\,
	datac => \ALT_INV_A0~input_o\,
	datad => \ALT_INV_A2~input_o\,
	datae => \ALT_INV_B1~input_o\,
	dataf => \ALT_INV_A3~input_o\,
	combout => \inst10|inst|inst3~0_combout\);

-- Location: LABCELL_X26_Y16_N9
\inst2|inst|inst1~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst2|inst|inst1~0_combout\ = ( \B2~input_o\ & ( (\A3~input_o\ & ((!\B1~input_o\) # (!\inst10|inst|inst3~0_combout\))) ) ) # ( !\B2~input_o\ & ( (\B1~input_o\ & (\A3~input_o\ & \inst10|inst|inst3~0_combout\)) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000101000000000000010100001111000010100000111100001010",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B1~input_o\,
	datac => \ALT_INV_A3~input_o\,
	datad => \inst10|inst|ALT_INV_inst3~0_combout\,
	dataf => \ALT_INV_B2~input_o\,
	combout => \inst2|inst|inst1~0_combout\);

-- Location: LABCELL_X26_Y16_N18
\inst6|inst|inst3~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst6|inst|inst3~0_combout\ = ( \A2~input_o\ & ( \inst4|inst|inst4~combout\ & ( (!\B2~input_o\ & (((\inst8|inst|inst1~combout\ & \inst10|inst|inst1~combout\)))) # (\B2~input_o\ & (((\inst10|inst|inst1~combout\) # (\inst8|inst|inst1~combout\)) # 
-- (\A1~input_o\))) ) ) ) # ( !\A2~input_o\ & ( \inst4|inst|inst4~combout\ & ( (\inst8|inst|inst1~combout\ & (((\B2~input_o\ & \A1~input_o\)) # (\inst10|inst|inst1~combout\))) ) ) ) # ( \A2~input_o\ & ( !\inst4|inst|inst4~combout\ & ( (\B2~input_o\ & 
-- (((\A1~input_o\ & \inst10|inst|inst1~combout\)) # (\inst8|inst|inst1~combout\))) ) ) ) # ( !\A2~input_o\ & ( !\inst4|inst|inst4~combout\ & ( (\B2~input_o\ & (\A1~input_o\ & (\inst8|inst|inst1~combout\ & \inst10|inst|inst1~combout\))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000001000001010001010100000001000011110001010101011111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B2~input_o\,
	datab => \ALT_INV_A1~input_o\,
	datac => \inst8|inst|ALT_INV_inst1~combout\,
	datad => \inst10|inst|ALT_INV_inst1~combout\,
	datae => \ALT_INV_A2~input_o\,
	dataf => \inst4|inst|ALT_INV_inst4~combout\,
	combout => \inst6|inst|inst3~0_combout\);

-- Location: LABCELL_X25_Y16_N48
\inst3|inst|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst3|inst|inst1~combout\ = ( \inst9|inst|inst4~combout\ & ( \inst6|inst|inst1~combout\ & ( !\inst3|inst2~combout\ $ (!\inst2|inst|inst1~0_combout\ $ (!\inst6|inst|inst3~0_combout\)) ) ) ) # ( !\inst9|inst|inst4~combout\ & ( \inst6|inst|inst1~combout\ & 
-- ( !\inst5|inst2~combout\ $ (!\inst3|inst2~combout\ $ (!\inst2|inst|inst1~0_combout\ $ (!\inst6|inst|inst3~0_combout\))) ) ) ) # ( \inst9|inst|inst4~combout\ & ( !\inst6|inst|inst1~combout\ & ( !\inst5|inst2~combout\ $ (!\inst3|inst2~combout\ $ 
-- (!\inst2|inst|inst1~0_combout\ $ (!\inst6|inst|inst3~0_combout\))) ) ) ) # ( !\inst9|inst|inst4~combout\ & ( !\inst6|inst|inst1~combout\ & ( !\inst3|inst2~combout\ $ (!\inst2|inst|inst1~0_combout\ $ (\inst6|inst|inst3~0_combout\)) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0011110011000011011010011001011001101001100101101100001100111100",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|ALT_INV_inst2~combout\,
	datab => \inst3|ALT_INV_inst2~combout\,
	datac => \inst2|inst|ALT_INV_inst1~0_combout\,
	datad => \inst6|inst|ALT_INV_inst3~0_combout\,
	datae => \inst9|inst|ALT_INV_inst4~combout\,
	dataf => \inst6|inst|ALT_INV_inst1~combout\,
	combout => \inst3|inst|inst1~combout\);

-- Location: LABCELL_X25_Y16_N24
\inst2|inst|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst2|inst|inst1~combout\ = !\inst6|inst|inst3~0_combout\ $ (!\inst2|inst|inst1~0_combout\)

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0011110000111100001111000011110000111100001111000011110000111100",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \inst6|inst|ALT_INV_inst3~0_combout\,
	datac => \inst2|inst|ALT_INV_inst1~0_combout\,
	combout => \inst2|inst|inst1~combout\);

-- Location: LABCELL_X25_Y16_N3
\inst2|inst|inst3~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst2|inst|inst3~0_combout\ = ( \inst6|inst|inst3~0_combout\ & ( (\A3~input_o\ & (((\inst10|inst|inst3~0_combout\ & \B1~input_o\)) # (\B2~input_o\))) ) ) # ( !\inst6|inst|inst3~0_combout\ & ( (\B2~input_o\ & (\A3~input_o\ & (\inst10|inst|inst3~0_combout\ 
-- & \B1~input_o\))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000001000000000000000100010001000100110001000100010011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B2~input_o\,
	datab => \ALT_INV_A3~input_o\,
	datac => \inst10|inst|ALT_INV_inst3~0_combout\,
	datad => \ALT_INV_B1~input_o\,
	dataf => \inst6|inst|ALT_INV_inst3~0_combout\,
	combout => \inst2|inst|inst3~0_combout\);

-- Location: LABCELL_X25_Y16_N27
\inst5|inst|inst3~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst5|inst|inst3~0_combout\ = ( \inst6|inst|inst1~combout\ & ( (\inst9|inst|inst4~combout\) # (\inst5|inst2~combout\) ) ) # ( !\inst6|inst|inst1~combout\ & ( (\inst5|inst2~combout\ & \inst9|inst|inst4~combout\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000010100000101000001010000010101011111010111110101111101011111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|ALT_INV_inst2~combout\,
	datac => \inst9|inst|ALT_INV_inst4~combout\,
	dataf => \inst6|inst|ALT_INV_inst1~combout\,
	combout => \inst5|inst|inst3~0_combout\);

-- Location: LABCELL_X25_Y16_N30
\inst7|inst|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst7|inst|inst1~combout\ = ( \inst5|inst|inst3~0_combout\ & ( \B3~input_o\ & ( !\inst2|inst|inst3~0_combout\ $ (!\A3~input_o\ $ (((\A2~input_o\) # (\inst2|inst|inst1~combout\)))) ) ) ) # ( !\inst5|inst|inst3~0_combout\ & ( \B3~input_o\ & ( 
-- !\inst2|inst|inst3~0_combout\ $ (!\A3~input_o\ $ (((\inst2|inst|inst1~combout\ & \A2~input_o\)))) ) ) ) # ( \inst5|inst|inst3~0_combout\ & ( !\B3~input_o\ & ( !\inst2|inst|inst1~combout\ $ (!\inst2|inst|inst3~0_combout\) ) ) ) # ( 
-- !\inst5|inst|inst3~0_combout\ & ( !\B3~input_o\ & ( \inst2|inst|inst3~0_combout\ ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000111100001111010110100101101000011110111000010111100010000111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|inst|ALT_INV_inst1~combout\,
	datab => \ALT_INV_A2~input_o\,
	datac => \inst2|inst|ALT_INV_inst3~0_combout\,
	datad => \ALT_INV_A3~input_o\,
	datae => \inst5|inst|ALT_INV_inst3~0_combout\,
	dataf => \ALT_INV_B3~input_o\,
	combout => \inst7|inst|inst1~combout\);

-- Location: LABCELL_X25_Y16_N6
\inst7|inst|inst3~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst7|inst|inst3~0_combout\ = ( \inst5|inst|inst3~0_combout\ & ( \B3~input_o\ & ( (!\inst2|inst|inst3~0_combout\ & (\A3~input_o\ & ((\A2~input_o\) # (\inst2|inst|inst1~combout\)))) # (\inst2|inst|inst3~0_combout\ & (((\A3~input_o\) # (\A2~input_o\)) # 
-- (\inst2|inst|inst1~combout\))) ) ) ) # ( !\inst5|inst|inst3~0_combout\ & ( \B3~input_o\ & ( (!\inst2|inst|inst3~0_combout\ & (\inst2|inst|inst1~combout\ & (\A2~input_o\ & \A3~input_o\))) # (\inst2|inst|inst3~0_combout\ & (((\inst2|inst|inst1~combout\ & 
-- \A2~input_o\)) # (\A3~input_o\))) ) ) ) # ( \inst5|inst|inst3~0_combout\ & ( !\B3~input_o\ & ( (\inst2|inst|inst1~combout\ & \inst2|inst|inst3~0_combout\) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000001010000010100000001000111110000011101111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|inst|ALT_INV_inst1~combout\,
	datab => \ALT_INV_A2~input_o\,
	datac => \inst2|inst|ALT_INV_inst3~0_combout\,
	datad => \ALT_INV_A3~input_o\,
	datae => \inst5|inst|ALT_INV_inst3~0_combout\,
	dataf => \ALT_INV_B3~input_o\,
	combout => \inst7|inst|inst3~0_combout\);

-- Location: LABCELL_X5_Y7_N0
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


