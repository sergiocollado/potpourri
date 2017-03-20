library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Add32 is

  port (
    AdderIn : in  std_logic_vector(6 downto 0);
    AdderOut : out std_logic_vector(6 downto 0);
    Jump32 : in  std_logic);

end Add32;


architecture RTL of Add32 is

begin 
  process(jump32,AdderIn)

  begin

    case jump32 is

      when '1' =>

        AdderOut <= std_logic_vector( unsigned(AdderIn) - 32 );

      when others =>

        AdderOut <= AdderIn;

    end case;               
    
  end process;

end RTL;
  


