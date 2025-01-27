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
        r_enable : in STD_LOGIC;
        -- serial data will input 1 bit at a time
        data_input : in STD_LOGIC;
        -- accounts for the 32 bits of each data
        data_output : out STD_LOGIC;
        parallel_out : out STD_LOGIC_VECTOR(127 downto 0));
end S_to_P_Converter;

architecture Behavioral of S_to_P_Converter is
-- set the shift-reg to be all zeros at start
    signal shift_reg : STD_LOGIC_VECTOR(31 downto 0) := x"00000000";
    signal counter : integer range 0 to 31;
    signal counter2 : integer range 0 to 4;
    signal test_sig : STD_LOGIC_VECTOR(31 downto 0);
-- BRAM memory block
signal adr : unsigned(3 downto 0) := "0000";
signal w1, w2, w3, w4 : STD_LOGIC;
signal do1, do2, do3, do4 : STD_LOGIC_VECTOR(31 downto 0);

component BRAM is
        port (
            clk : in STD_LOGIC;
            write_enable : in STD_LOGIC;
            read_enable : in STD_LOGIC;
            addr : in STD_LOGIC_VECTOR(3 downto 0);
            data_in : in STD_LOGIC_VECTOR(31 downto 0);
            data_out : out STD_LOGIC_VECTOR(31 downto 0));
end component;

begin
process (clk)
begin
    if rising_edge(clk) then
        w1 <= '0';
        w2 <= '0';
        w3 <= '0';
        w4 <= '0';
        shift_reg <= shift_reg(30 downto 0) & data_input;
        counter <= counter +1;
        if (counter = 32) then
            counter <= 0;
            counter2 <= counter2 + 1;
            test_sig <= shift_reg;
        if (counter2 = 1) then
            w1 <= '1';
        end if;
        if (counter2 = 2) then
            w2 <= '1';
        end if;
        if (counter2 = 3) then
            w3 <= '1';
        end if;
        if (counter2 = 4) then
            w4 <= '1';
            counter2 <= 0;
        end if;
            shift_reg <= (others => '0');
        end if;
    end if;
end process;
data_output <= shift_reg(31);

mem_block1: BRAM port map(
    clk => clk,
    write_enable => w1,
    read_enable => r_enable,
    addr => "0000",
    data_in => test_sig,
    data_out => do1);
mem_block2: BRAM port map(
    clk => clk,
    write_enable => w2,
    read_enable => r_enable,
    addr => "0000",
    data_in => test_sig,
    data_out => do2);
mem_block3: BRAM port map(
    clk => clk,
    write_enable => w3,
    read_enable => r_enable,
    addr => "0000",
    data_in => test_sig,
    data_out => do3);
mem_block4: BRAM port map(
    clk => clk,
    write_enable => w4,
    read_enable => r_enable,
    addr => "0000",
    data_in => test_sig,
    data_out => do4);
parallel_out <= do1&do2&do3&do4;
end Behavioral;
