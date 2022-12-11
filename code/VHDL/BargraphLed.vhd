library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity BargraphLed is

  port (
    Ain   : in  std_logic_vector(6 downto 0);
    enable: in  std_logic;
    Clk   : in  std_logic;
    BarOut: out std_logic;
    Reset : in  std_logic);

end BarGraphLed;

architecture RTL of BargraphLed is
 constant S0idle : std_logic_vector(2 downto 0):="000";  --OFF
 constant S1 : std_logic_vector(2 downto 0) := "001";
 constant S2on : std_logic_vector(2 downto 0) := "010";
 constant S3 : std_logic_vector(2 downto 0) := "011";
 constant S4off : std_logic_vector(2 downto 0) :="100";
 
 
  signal sig : std_logic;
  
begin  -- RTL

  process (Clk, Reset,enable)
    
    variable PresentState, NextState : std_logic_vector(2 downto 0) := "000";

  begin  -- process

    if Reset = '1' then

      sig <= '0';
      PresentState := S0idle;
      NextState := S0idle;

    elsif rising_edge(Clk) and enable = '1' then

      PresentState := NextState;

      case PresentState is
        
        when S0idle  =>

          if unsigned(Ain) = 79 or unsigned(Ain) = 111 then

            NextState := S1;

          else

            NextState := S0idle;
            
          end if;

        when S1 =>

          if unsigned(Ain) = 79 or unsigned(Ain) = 111 then

            NextState := S1;

          elsif unsigned(Ain) = 78 or unsigned(Ain) = 110 then
            sig <= '1';                -- I dont wait to next cicles
            NextState := S2ON;

            elsif unsigned(Ain) = 70 or unsigned(Ain) = 102 then
              
            NextState := S3;
          else

            NextState :=S0idle;
            
          end if;

        when S2ON =>

          sig <= '1';

          if unsigned(Ain) = 79 or unsigned(Ain) = 111 then

            NextState := S1;

          else

            NextState := S0idle;
            
          end if;

        when S3 => 

          if unsigned(Ain) = 70 or unsigned(Ain) = 102 then
            sig <= '0';
            NextState := S4off;
            
            elsif unsigned(Ain) = 79 or unsigned(Ain) = 111 then

            NextState := S1;
            else
              NextState := S0idle;
            end if;

        when S4off =>
            sig <= '0';
            if unsigned(Ain) = 79 or unsigned(Ain) = 111 then

            NextState := S1;
            else
              NextState := S0idle;

             end if;
          
        when others =>

          report "illegal state in bar swich" severity error;
          
      end case;
      
    end if;
    
  end process;
  BarOut <= sig;
  
end RTL;


