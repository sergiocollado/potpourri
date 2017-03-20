library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ShiftReg is

  port (
    Clk    : in  std_logic;
    Enable : in  std_logic;
    D      : in  std_logic;
    Q      : out std_logic_vector(8 downto 0));

end ShiftReg;

architecture RTL of ShiftReg is

  
  
begin  -- RTL
  
  process (Clk, Enable, D)
    variable s_reg : std_logic_vector(8 downto 0) := "000000000";
  begin
    
    if rising_edge(Clk) then
      if Enable = '1' then
        s_reg := D & s_reg(8 downto 1);
      end if;
    end if;
    Q <= s_reg;
  end process;
  
end RTL;







