----------------------------------------------------------------------------------
-- Engineer: Nethania Morales
-- 
-- Module Name: S_to_P_Converter_TB - Behavioral
--
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity S_to_P_Converter_TB is
--  Port ( );
end S_to_P_Converter_TB;

architecture Behavioral of S_to_P_Converter_TB is
component S_to_P_Converter is
    port (
        clk : in STD_LOGIC;
        rst : in STD_LOGIC;
        r_enable : in STD_LOGIC;
        -- serial data will input 1 bit at a time
        data_input : in STD_LOGIC;
        -- accounts for the 32 bits of each data
        data_output : out STD_LOGIC;
        parallel_out : out STD_LOGIC_VECTOR(127 downto 0));
end component;

signal clk_tb : STD_LOGIC;
signal rst_tb : STD_LOGIC;
signal r_enable_tb : STD_LOGIC;
signal data_input_tb : STD_LOGIC;
signal data_output_tb : STD_LOGIC;
signal parallel_out_tb : STD_LOGIC_VECTOR(127 downto 0);

begin

uut1 : S_to_P_Converter port map(
    clk => clk_tb,
    rst => rst_tb,
    r_enable => r_enable_tb,
    data_input => data_input_tb,
    data_output => data_output_tb,
    parallel_out => parallel_out_tb);
    
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
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '0';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '0';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '0';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '0';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '0';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '0';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '0';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '1';
    wait for 20ns;
    data_input_tb <= '0';
    wait for 20ns;
end process;

process
begin
r_enable_tb <= '0';
wait for 3320ns;
r_enable_tb <= '1';
wait;
end process;

end Behavioral;