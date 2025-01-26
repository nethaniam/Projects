----------------------------------------------------------------------------------
-- Engineer: Nethania Morales
-- 
-- Create Date: 05/15/2024 06:19:59 PM
-- Module Name: Shift_reg_TB - Behavioral
--
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Shift_reg_TB is
--  Port ( );
end Shift_reg_TB;

architecture Behavioral of Shift_reg_TB is
component S_to_P_Converter is
    port (
        clk : in STD_LOGIC;
        rst : in STD_LOGIC;
        -- serial data will input 1 bit at a time
        data_input : in STD_LOGIC;
        -- accounts for the 32 bits of each data
        data_output : out STD_LOGIC);
end component;

signal clk_tb : STD_LOGIC;
signal rst_TB : STD_LOGIC;
signal data_input_TB : STD_LOGIC;
signal data_output_TB : STD_LOGIC;

begin

uut1 : S_to_P_Converter port map(
    clk => clk_tb,
    rst => rst_tb,
    data_input => data_input_tb,
    data_output => data_output_tb);
    
-- clk - period = 20ns
process
begin
    rst_tb <= '0';
    clk_tb <= '1';
    wait for 10ns;
    clk_tb <= '0';
    wait for 10ns;
end process;

process
begin
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '0';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '0';
    wait for 20ns;
end process;

end Behavioral;
