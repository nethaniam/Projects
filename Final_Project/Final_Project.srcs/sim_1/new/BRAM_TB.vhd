----------------------------------------------------------------------------------
-- Engineer: Nethania Morales
--
-- Module Name: BRAM_TB - Behavioral
--
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity BRAM_TB is
--  Port ( );
end BRAM_TB;

architecture Behavioral of BRAM_TB is
component BRAM is
    port (
        clk : in STD_LOGIC;
        write_enable : in STD_LOGIC;
        read_enable : in STD_LOGIC;
        addr : in STD_LOGIC_VECTOR(3 downto 0);
        data_in : in STD_LOGIC_VECTOR(31 downto 0);
        data_out : out STD_LOGIC_VECTOR(31 downto 0));
end component;

signal clk_tb : STD_LOGIC;
signal write_enable_tb : STD_LOGIC;
signal read_enable_tb : STD_LOGIC;
signal addr_tb : STD_LOGIC_VECTOR(3 downto 0);
signal data_in_tb : STD_LOGIC_VECTOR(31 downto 0);
signal data_out_tb : STD_LOGIC_VECTOR(31 downto 0);

begin
uut1: BRAM port map(
    clk => clk_tb,
    write_enable => write_enable_tb,
    read_enable => read_enable_tb,
    addr => addr_tb,
    data_in => data_in_tb,
    data_out => data_out_tb);
    
process
begin
    clk_tb <= '1';
    wait for 10ns;
    clk_tb <= '0';
    wait for 10ns;
end process;

process
begin
    write_enable_tb <= '1';
    addr_tb <= "0000";
    data_in_tb <= x"FFFFFFFF";
    wait for 10ns;
    read_enable_tb <= '1';
    wait;
end process;
end Behavioral;
