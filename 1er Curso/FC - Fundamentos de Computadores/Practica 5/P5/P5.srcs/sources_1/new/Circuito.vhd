----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 23.11.2024 13:54:04
-- Design Name: 
-- Module Name: Circuito - A_Circuito
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Circuito is
    Port ( E : in STD_LOGIC_VECTOR (4 downto 0);
           S : out STD_LOGIC_VECTOR (3 downto 0));
end Circuito;

architecture A_Circuito of Circuito is

begin
process(E) -- Sensibilidad al cambio de E
begin
    case E is
        when "01100" => S(3) <= '0'; -- 0
        when "11000"  => S(3) <= '0'; -- 1
        when "10100" => S(3) <= '0'; -- 2
        when "10010"  => S(3) <= '0'; -- 3
        when "01010" => S(3) <= '0'; -- 4
        when "00110"  => S(3) <= '0'; -- 5
        when "10001" => S(3) <= '0'; -- 6
        when "01001"  => S(3) <= '0'; -- 7
        when "00101" => S(3) <= '0'; -- 8
        when "00011" => S(3) <= '1'; -- 9
        when others  => S(3) <= '1'; -- Por defecto, S3 apagado
    end case;
    end process;
    process(E)
    begin
    if E = "01100" then
     S(2) <= '0';
    elsif E= "11000" then 
    S(2) <= '0';
    elsif E= "10100" then
     S(2) <= '0';
    elsif E= "10010" then
     S(2) <= '0';
    elsif E= "01010" then 
    S(2) <= '1';
    elsif E= "00110" then
     S(2) <= '1';
    elsif E= "10001" then
     S(2) <= '1';
    elsif E= "01001" then
     S(2) <= '1';
    elsif E= "00101" then 
    S(2) <= '0';
    elsif E= "00011" then 
    S(2) <= '0';
    end if;
    end process;
    process(E)
    begin
    with E select
        S(1) <= '0' when "01100",
                 '0' when "11000",
                 '1' when "10100",
                 '1' when "10010",
                 '0' when "01010",
                 '0' when "00110",
                 '1' when "10001",
                 '1' when "01001",
                 '0' when "00101",
                 '0' when "00011",
                 '0' when others;
            end process;
            process(E)
            begin
   S(0) <= '0' when E = "01100" else
             '1' when E = "11000" else
             '0' when E = "10100" else
             '1' when E = "10010" else
             '0' when E = "01010" else
             '1' when E = "00110" else
             '0' when E = "10001" else
             '1' when E = "01001" else
             '0' when E = "00101" else
             '1' when E = "00011" else
             '0'; -- Por defecto
end process;
end A_Circuito;
