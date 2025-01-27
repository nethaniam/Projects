----------------------------------------------------------------------------------
-- Engineer: Nethania Morales 
--  
-- Module Name: BRAM - Behavioral
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity BRAM is
    port (
        clk : in STD_LOGIC;
        write_enable : in STD_LOGIC;
        read_enable : in STD_LOGIC;
        addr : in STD_LOGIC_VECTOR(3 downto 0);
        data_in : in STD_LOGIC_VECTOR(31 downto 0);
        data_out : out STD_LOGIC_VECTOR(31 downto 0));
end BRAM;

architecture Behavioral of BRAM is
type bram_type is array (14 downto 0) of std_logic_vector(31 downto 0);
-- empty memory block
signal BRAM_1 : bram_type;
begin
process(clk)
begin
    if rising_edge(clk) then
    if (write_enable = '1') then
        BRAM_1(to_integer(unsigned(addr))) <= data_in;
    end if;
    if (read_enable = '1') then
        data_out <= BRAM_1(to_integer(unsigned(addr)));
    end if;
    end if;
end process;
end Behavioral;
