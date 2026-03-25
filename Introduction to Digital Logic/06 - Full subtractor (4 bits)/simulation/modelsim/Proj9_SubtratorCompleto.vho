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

-- DATE "07/10/2021 03:14:29"

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

ENTITY 	Proj9_SubtratorCompleto IS
    PORT (
	S0 : OUT std_logic;
	A0 : IN std_logic;
	B0 : IN std_logic;
	S1 : OUT std_logic;
	A1 : IN std_logic;
	B1 : IN std_logic;
	S2 : OUT std_logic;
	A2 : IN std_logic;
	B2 : IN std_logic;
	S3 : OUT std_logic;
	A3 : IN std_logic;
	B3 : IN std_logic;
	ESTOURO : OUT std_logic
	);
END Proj9_SubtratorCompleto;

-- Design Ports Information
-- S0	=>  Location: PIN_AA2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- S1	=>  Location: PIN_AA1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- S2	=>  Location: PIN_W2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- S3	=>  Location: PIN_Y3,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ESTOURO	=>  Location: PIN_N2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A0	=>  Location: PIN_U13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B0	=>  Location: PIN_AA15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A1	=>  Location: PIN_V13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B1	=>  Location: PIN_AB15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A2	=>  Location: PIN_T13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B2	=>  Location: PIN_AA14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- A3	=>  Location: PIN_T12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- B3	=>  Location: PIN_AA13,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF Proj9_SubtratorCompleto IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_S0 : std_logic;
SIGNAL ww_A0 : std_logic;
SIGNAL ww_B0 : std_logic;
SIGNAL ww_S1 : std_logic;
SIGNAL ww_A1 : std_logic;
SIGNAL ww_B1 : std_logic;
SIGNAL ww_S2 : std_logic;
SIGNAL ww_A2 : std_logic;
SIGNAL ww_B2 : std_logic;
SIGNAL ww_S3 : std_logic;
SIGNAL ww_A3 : std_logic;
SIGNAL ww_B3 : std_logic;
SIGNAL ww_ESTOURO : std_logic;
SIGNAL \~QUARTUS_CREATED_GND~I_combout\ : std_logic;
SIGNAL \A0~input_o\ : std_logic;
SIGNAL \B0~input_o\ : std_logic;
SIGNAL \inst|inst~combout\ : std_logic;
SIGNAL \A1~input_o\ : std_logic;
SIGNAL \B1~input_o\ : std_logic;
SIGNAL \inst1|inst1~combout\ : std_logic;
SIGNAL \B2~input_o\ : std_logic;
SIGNAL \A2~input_o\ : std_logic;
SIGNAL \inst2|inst1~combout\ : std_logic;
SIGNAL \B3~input_o\ : std_logic;
SIGNAL \A3~input_o\ : std_logic;
SIGNAL \inst1|inst6~0_combout\ : std_logic;
SIGNAL \inst3|inst1~combout\ : std_logic;
SIGNAL \inst3|inst6~0_combout\ : std_logic;
SIGNAL \ALT_INV_B3~input_o\ : std_logic;
SIGNAL \ALT_INV_A3~input_o\ : std_logic;
SIGNAL \ALT_INV_B2~input_o\ : std_logic;
SIGNAL \ALT_INV_A2~input_o\ : std_logic;
SIGNAL \ALT_INV_B1~input_o\ : std_logic;
SIGNAL \ALT_INV_A1~input_o\ : std_logic;
SIGNAL \ALT_INV_B0~input_o\ : std_logic;
SIGNAL \ALT_INV_A0~input_o\ : std_logic;
SIGNAL \inst1|ALT_INV_inst6~0_combout\ : std_logic;

BEGIN

S0 <= ww_S0;
ww_A0 <= A0;
ww_B0 <= B0;
S1 <= ww_S1;
ww_A1 <= A1;
ww_B1 <= B1;
S2 <= ww_S2;
ww_A2 <= A2;
ww_B2 <= B2;
S3 <= ww_S3;
ww_A3 <= A3;
ww_B3 <= B3;
ESTOURO <= ww_ESTOURO;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
\ALT_INV_B3~input_o\ <= NOT \B3~input_o\;
\ALT_INV_A3~input_o\ <= NOT \A3~input_o\;
\ALT_INV_B2~input_o\ <= NOT \B2~input_o\;
\ALT_INV_A2~input_o\ <= NOT \A2~input_o\;
\ALT_INV_B1~input_o\ <= NOT \B1~input_o\;
\ALT_INV_A1~input_o\ <= NOT \A1~input_o\;
\ALT_INV_B0~input_o\ <= NOT \B0~input_o\;
\ALT_INV_A0~input_o\ <= NOT \A0~input_o\;
\inst1|ALT_INV_inst6~0_combout\ <= NOT \inst1|inst6~0_combout\;

-- Location: IOOBUF_X0_Y18_N79
\S0~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|inst~combout\,
	devoe => ww_devoe,
	o => ww_S0);

-- Location: IOOBUF_X0_Y18_N96
\S1~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst1|inst1~combout\,
	devoe => ww_devoe,
	o => ww_S1);

-- Location: IOOBUF_X0_Y18_N62
\S2~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|inst1~combout\,
	devoe => ww_devoe,
	o => ww_S2);

-- Location: IOOBUF_X0_Y18_N45
\S3~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst3|inst1~combout\,
	devoe => ww_devoe,
	o => ww_S3);

-- Location: IOOBUF_X0_Y19_N39
\ESTOURO~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \inst3|inst6~0_combout\,
	devoe => ww_devoe,
	o => ww_ESTOURO);

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

-- Location: MLABCELL_X34_Y2_N30
\inst|inst\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst|inst~combout\ = !\A0~input_o\ $ (!\B0~input_o\)

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0110011001100110011001100110011001100110011001100110011001100110",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_A0~input_o\,
	datab => \ALT_INV_B0~input_o\,
	combout => \inst|inst~combout\);

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

-- Location: MLABCELL_X34_Y2_N33
\inst1|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst1|inst1~combout\ = ( \B1~input_o\ & ( !\A1~input_o\ $ (((!\A0~input_o\ & \B0~input_o\))) ) ) # ( !\B1~input_o\ & ( !\A1~input_o\ $ (((!\B0~input_o\) # (\A0~input_o\))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0010110100101101001011010010110111010010110100101101001011010010",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_A0~input_o\,
	datab => \ALT_INV_B0~input_o\,
	datac => \ALT_INV_A1~input_o\,
	dataf => \ALT_INV_B1~input_o\,
	combout => \inst1|inst1~combout\);

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

-- Location: MLABCELL_X34_Y2_N36
\inst2|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst2|inst1~combout\ = ( \A0~input_o\ & ( \B1~input_o\ & ( !\B2~input_o\ $ (!\A1~input_o\ $ (!\A2~input_o\)) ) ) ) # ( !\A0~input_o\ & ( \B1~input_o\ & ( !\B2~input_o\ $ (!\A2~input_o\ $ (((!\A1~input_o\) # (\B0~input_o\)))) ) ) ) # ( \A0~input_o\ & ( 
-- !\B1~input_o\ & ( !\B2~input_o\ $ (!\A2~input_o\) ) ) ) # ( !\A0~input_o\ & ( !\B1~input_o\ & ( !\B2~input_o\ $ (!\A2~input_o\ $ (((!\A1~input_o\ & \B0~input_o\)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0101101010010110010110100101101010010110101001011001011010010110",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B2~input_o\,
	datab => \ALT_INV_A1~input_o\,
	datac => \ALT_INV_A2~input_o\,
	datad => \ALT_INV_B0~input_o\,
	datae => \ALT_INV_A0~input_o\,
	dataf => \ALT_INV_B1~input_o\,
	combout => \inst2|inst1~combout\);

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

-- Location: MLABCELL_X34_Y2_N42
\inst1|inst6~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst1|inst6~0_combout\ = ( \A0~input_o\ & ( \B1~input_o\ & ( !\A1~input_o\ ) ) ) # ( !\A0~input_o\ & ( \B1~input_o\ & ( (!\A1~input_o\) # (\B0~input_o\) ) ) ) # ( !\A0~input_o\ & ( !\B1~input_o\ & ( (!\A1~input_o\ & \B0~input_o\) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000011001100000000000000000011001100111111111100110011001100",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \ALT_INV_A1~input_o\,
	datad => \ALT_INV_B0~input_o\,
	datae => \ALT_INV_A0~input_o\,
	dataf => \ALT_INV_B1~input_o\,
	combout => \inst1|inst6~0_combout\);

-- Location: MLABCELL_X34_Y2_N18
\inst3|inst1\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst3|inst1~combout\ = ( \inst1|inst6~0_combout\ & ( !\B3~input_o\ $ (!\A3~input_o\ $ (((!\A2~input_o\) # (\B2~input_o\)))) ) ) # ( !\inst1|inst6~0_combout\ & ( !\B3~input_o\ $ (!\A3~input_o\ $ (((\B2~input_o\ & !\A2~input_o\)))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0110001110011100011000111001110011000110001110011100011000111001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B2~input_o\,
	datab => \ALT_INV_B3~input_o\,
	datac => \ALT_INV_A2~input_o\,
	datad => \ALT_INV_A3~input_o\,
	dataf => \inst1|ALT_INV_inst6~0_combout\,
	combout => \inst3|inst1~combout\);

-- Location: MLABCELL_X34_Y2_N21
\inst3|inst6~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \inst3|inst6~0_combout\ = ( \inst1|inst6~0_combout\ & ( (!\B3~input_o\ & (!\A3~input_o\ & ((!\A2~input_o\) # (\B2~input_o\)))) # (\B3~input_o\ & (((!\A3~input_o\) # (!\A2~input_o\)) # (\B2~input_o\))) ) ) # ( !\inst1|inst6~0_combout\ & ( (!\B3~input_o\ & 
-- (\B2~input_o\ & (!\A3~input_o\ & !\A2~input_o\))) # (\B3~input_o\ & ((!\A3~input_o\) # ((\B2~input_o\ & !\A2~input_o\)))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0111000100110000011100010011000011110011011100011111001101110001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_B2~input_o\,
	datab => \ALT_INV_B3~input_o\,
	datac => \ALT_INV_A3~input_o\,
	datad => \ALT_INV_A2~input_o\,
	dataf => \inst1|ALT_INV_inst6~0_combout\,
	combout => \inst3|inst6~0_combout\);

-- Location: LABCELL_X16_Y11_N0
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


