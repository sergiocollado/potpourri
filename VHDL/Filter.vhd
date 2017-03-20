library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Filter is

  port (
    Clk, Reset : in  std_logic;
    din        : in  std_logic_vector(7 downto 0);
    readEn     : in  std_logic;
    writeEn    : out std_logic;
    dout       : out std_logic_vector(7 downto 0));

end Filter;

architecture RTL of Filter is

        constant Idle : std_logic_vector(1 downto 0) := "00";
        constant S0 : std_logic_vector(1 downto 0) := "01";
        constant S1 : std_logic_vector(1 downto 0) := "10";
        constant S2 : std_logic_vector(1 downto 0) := "11";


  

begin  -- RTL

  process (Clk, Reset,readEn)

    variable PresentState, NextState : std_logic_vector(1 downto 0) :="00";
    variable Key : std_logic_vector(7 downto 0);
  begin  -- process

    if Reset = '1' then
      dout  <= "00000000";
      writeEn <= '0';
      PresentState := Idle;
      NextState := Idle;
      
      
    elsif rising_edge(Clk)  then
      
      PresentState := NextState;

      case PresentState is

        when Idle =>

          if readEn ='1' and( din = "00011100" or din = "00110010" or din = "00100001" or din = "00100011" or din = "00100100" or din = "00101011" or din = "00110100" or
            din = "00110011" or din = "01000011" or din = "00111011" or din = "01000010" or din = "01001011" or din = "00111010" or din = "00110001" or
            din = "01000100" or din = "01001101" or din = "00010101" or din = "00101101" or din = "00011011" or din = "00101100" or din = "00111100" or
            din = "00101010" or din = "00011101" or din = "00100010" or din = "00110101" or din = "00011010") then
            
            NextState := S0;
            Key := din;
            dout  <= key;
            writeEn <= '1';
            
          else
            
            NextState := Idle;
            dout <= "00000000";
            writeEn <= '0';

          end if;

        when S0 =>

         if readEn ='1' then
           
          if din = "11110000" then
            
            NextState := S1;
            dout  <= "00000000";
            writeEn <= '0';

          else

            NextState := S0;
            dout  <= Key;
            writeEn <= '1';

          end if;

          else
            writeEn <= '0';
          end if;
          
        when S1 =>
          if readEn ='1' then
            
          if din = Key then
            WriteEn <= '0';
            
            NextState := idle;

          else

            NextState := S1;
            WriteEn <= '0';

          end if;

         else
          dout <= "00000000";
          writeEn <= '0';
         end if;
        when others =>

          report "illegal code " severity error;

      end case;

    end if;

  end process;

end RTL;
