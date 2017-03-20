
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity EnAdd32 is
  
  port (
    Clk, Reset : in  std_logic;
    din        : in  std_logic_vector(7 downto 0);
    readEn     : in  std_logic;
    shiftOut   : out std_logic);

end EnAdd32;

architecture RTL of EnAdd32 is
constant Idle : integer := 0;
constant S0 : integer := 1;
begin  -- RTL

process (Clk, Reset,readEn)
variable PresentState : integer range 0 to 1  := 0 ;
variable NextState : integer range 0 to 1  := 0;
variable Key : std_logic_vector(7 downto 0);

    begin  -- process

    if Reset = '1' then

      shiftout  <= '0';
      PresentState := Idle;
      NextState := Idle;
      
    elsif rising_edge(Clk) and readEn = '1' then
      
      PresentState := NextState;

      case PresentState is
        
        when Idle =>
          
          if ( din = "00010010" or din ="01011001") then      --h59 h12 
            key := din; 
            NextState := S0; 
            ShiftOut <= '1';

          else
            
            NextState := Idle;
            ShiftOut <= '0';

          end if;

        when S0 =>

          if din = key  then

            NextState := Idle;
            ShiftOut <= '0';

          else
            
            NextState := S0;
            ShiftOut <= '1';
            
          end if;
          

        when others =>
                    null;
          
      end case;

    end if;

  end process;

end RTL;
