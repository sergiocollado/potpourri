library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity RSTransmitter is

  port (
    
    Clk   : in  std_logic;
    Sout  : out std_logic;
    Reset : in  std_logic;
    Pin   : in  std_logic_vector(6 downto 0);
    en    : in  std_logic);

end RSTransmitter;


architecture RTL of RSTransmitter is
 constant Idle : std_logic_vector(3 downto 0) := "0000";
 constant StartBit : std_logic_vector(3 downto 0) := "0001";
 constant S0 : std_logic_vector(3 downto 0) := "0010";
 constant S1 : std_logic_vector(3 downto 0) := "0011";
 constant S2 : std_logic_vector(3 downto 0) := "0100";
 constant S3 : std_logic_vector(3 downto 0) := "0101";
 constant S4 : std_logic_vector(3 downto 0) := "0110";
 constant S5 : std_logic_vector(3 downto 0) := "0111";
 constant S6 : std_logic_vector(3 downto 0) := "1000";
 constant StopBit : std_logic_vector(3 downto 0) := "1001";

begin  -- RTL

  process (Clk, Reset)
    
    variable PresentState, NextState : std_logic_vector(3 downto 0) :="0000";
    variable cicles : integer range 0 to 174;
  begin  -- process

    if Reset = '1' then

      Sout <= '1';
      PresentState := "0000";
      NextState := "0000";
      cicles := 0;

    elsif rising_edge(Clk) then
      
      PresentState := NextState;
      
      case PresentState is
        
        when Idle =>

          Sout <= '1';
          cicles := 0;
          
          if en = '1' then

            NextState := StartBit;

          else

            NextState := Idle;

          end if;

        when StartBit =>
          
          Sout <= '0';

          if cicles = 174 then

            NextState := S0;
            cicles := 0;

          else

            cicles := cicles + 1;
            NextState := StartBit;
            
          end if;

        when S0 =>
          
          Sout <= Pin(0);
          
          if cicles = 174 then

            NextState := S1;
            cicles := 0;

          else

            cicles := cicles + 1;
            NextState := S0;

          end if;

        when S1 =>
          
          Sout <= Pin(1);

          if cicles= 174 then

            NextState := S2;
            cicles := 0;

          else

            cicles := cicles + 1;
            NextState := S1;

          end if;

        when S2 =>

          Sout <= Pin(2);

          if cicles= 174 then

            NextState := S3;
            cicles := 0;

          else

            cicles := cicles + 1;
            NextState := S2;

          end if;
          
        when S3 =>

          Sout <= Pin(3);

          if cicles = 174 then

            NextState := S4;
            cicles := 0;

          else

            cicles := cicles + 1;
            NextState := S3;

          end if;

        when S4 =>

          Sout <= Pin(4);

          if cicles = 174 then

            NextState := S5;
            cicles := 0;

          else

            cicles := cicles + 1;
            NextState := S4;

          end if;

        when S5 =>

          Sout <= Pin(5);

          if cicles = 174 then

            NextState := S6;
            cicles := 0;

          else

            cicles := cicles + 1;
            NextState := S5;

          end if;

        when S6 =>

          Sout <= Pin(6);

          if cicles = 174 then

            NextState := StopBit;
            cicles := 0;

          else

            cicles := cicles+1;
            NextState := S6;

          end if;

        when StopBit =>

          Sout <= '1';

          if cicles = 174 then

            NextState := Idle;
            cicles := 0;

          else

            cicles := cicles + 1;
            NextState := StopBit;

          end if;                  

        when others =>

          report "error state sirial TRANSMITTER" severity error;

      end case;
      
    end if;    
    
  end process;

end RTL;
