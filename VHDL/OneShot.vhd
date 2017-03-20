library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity OneShot is

  port (
    Clk, Reset : in  std_logic;
    D          : in  std_logic;
    Pulse      : out std_logic);

end OneShot;

architecture RTL of OneShot is

  signal D_ff : std_logic;

begin  -- RTL

  process (Clk, Reset)
  begin  -- process

    if Reset = '1' then
      D_ff  <= '0';
    elsif rising_edge(Clk) then
       D_ff <= D;
    end if;
  end process;
 Pulse <= not(D) and D_ff;
 end RTL;

