----------------------------------------------------------------------------------
-- Engineer: Nethania Morales
-- 
-- Module Name: S_to_P_Converter - Behavioral
--
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity S_to_P_Converter is
    port (
        clk : in STD_LOGIC;
        rst : in STD_LOGIC;
        -- serial data will input 1 bit at a time
        data_input : in STD_LOGIC;
        -- accounts for the 32 bits of each data
        data_output : out STD_LOGIC);
end S_to_P_Converter;

architecture Behavioral of S_to_P_Converter is
    signal shift_reg : STD_LOGIC_VECTOR(31 downto 0);
    signal counter : integer range 0 to 31;
    
begin
--    process (clk)
--    begin
--        if rising_edge(clk) then
--            shift_reg(0) <= data_input; 
--            for i in 0 downto 30 loop
--                shift_reg(i+1) <= shift_reg(i);
--            end loop;   
--            shift_reg(0) <= data_input;              
--        end if;
--    end process;
--data_output <= shift_reg(31);
end Behavioral;
