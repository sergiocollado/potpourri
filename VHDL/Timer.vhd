
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Timer is

  port (
    Clk, Reset : in  std_logic;
    FifoEmpty  : in  std_logic;
    FifoRead   : out std_logic);

end Timer;

architecture timeMachine of Timer is

begin  -- timeMachine

  process (Clk,Reset)
variable cicles : integer range 0 to 20000000 := 0;         -- counts the cycles (10000 equals halfa a second)
  begin  -- process
    if Reset ='1' then
      FifoRead <= '0';
      cicles := 0;
    elsif rising_edge(Clk) then
      if FifoEmpty ='0' then 
        if cicles = 20000000 then
         FifoRead <= '1';
           cicles := 0;
        else
          FifoRead <= '0';
          cicles := cicles +1;
          
        end if;
      end if;
    end if;
  end process;

end timeMachine;

