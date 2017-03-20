library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity RSReceiver is

  port (
    Reset : in  std_logic;
    OK    : in  std_logic;
    Sin   : in  std_logic;
    Clk   : in  std_logic;
    Pout  : out std_logic_vector(6 downto 0);
    writeEn : out std_logic);
   

end RSReceiver;

architecture RTL of RSReceiver is

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
   

  signal reg1 : std_logic_vector(6 downto 0);
  
begin  -- RTL

  process (Clk, Reset, OK)
    variable PresentState, NextState : std_logic_vector(3 downto 0) :="0000";
    variable cicles : integer range 0 to 174;
  begin  -- process

    if Reset = '1' then
      writeEn <= '0';
      reg1 <= "0000000";
      PresentState := Idle;
      NextState := Idle;
      cicles := 0;

    elsif rising_edge(Clk) and OK = '1' then

      PresentState := NextState;

      case PresentState is
        
        when Idle =>

          reg1 <= "0000000";

          if Sin = '0' then

            cicles := 0;
            NextState := StartBit;

          else

            NextState := Idle;
            
          end if;

          writeEn <= '0';

        when StartBit =>

          cicles := cicles + 1;

          if cicles = 87 then

            if Sin = '0' then

              cicles := 0;
              NextState := S0;

            else

              report "Errorr in the start bit from receiver" severity error;
              NextState := Idle;
              
            end if;

          else
            
            NextState := StartBit;

          end if;

          writeEn <= '0';

        when S0 =>

          cicles := cicles + 1;

          if cicles = 174 then

            reg1(0) <= Sin;
            cicles := 0;
            NextState := S1;

          else

            NextState := S0;
            
          end if;

          writeEn <= '0';

        when S1 =>

          cicles := cicles + 1;

          if cicles = 174 then

            reg1(1) <= Sin;
            cicles := 0;
            NextState := S2;

          else

            NextState := S1;
            
          end if;

          writeEn <= '0';

        when S2 =>

          cicles := cicles + 1;

          if cicles = 174 then

            reg1(2) <= Sin;
            cicles := 0;
            NextState := S3;

          else

            NextState := S2;
            
          end if;

          writeEn <= '0';

        when S3 =>

          cicles := cicles + 1;

          if cicles = 174 then

            reg1(3) <= Sin;
            cicles := 0;
            NextState := S4;

          else

            NextState := S3;
            
          end if;

          writeEn <= '0';

        when S4 =>

          cicles := cicles + 1;

          if cicles = 174 then

            reg1(4) <= Sin;
            cicles := 0;
            NextState := S5;

          else

            NextState := S4;
            
          end if;

          writeEn <= '0';

        when S5 =>

          cicles := cicles + 1;

          if cicles = 174 then

            reg1(5) <= Sin;
            cicles := 0;
            NextState := S6;

          else

            NextState := S5;
            
          end if;

          writeEn <= '0';

        when S6 =>

          cicles := cicles + 1;

          if cicles = 174 then

            reg1(6) <= Sin;
            cicles := 0;
            NextState := StopBit;

          else

            NextState := S6;
            
          end if;

          writeEn <= '0';

        when StopBit =>

          cicles := cicles + 1;

          if cicles = 174 then
            
            if Sin = '1' then
            
              writeEn <= '1';

            else

              writeEn <= '0';
              report "Stop bit error from receiver " severity error;
            
            end if;

            NextState := Idle;

          else
             writeEn <= '0';
            NextState := StopBit;

          end if;
            
        when others =>

          report "illegal state in state machine receiver" severity error;
          
      end case;
      
    end if;

    Pout <= reg1;
    
  end process;

end RTL;
