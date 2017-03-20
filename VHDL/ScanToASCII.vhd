library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ScanToASCII is

  port (
    Din : in  std_logic_vector(7 downto 0);
    Dout : out std_logic_vector(6 downto 0)); 

end ScanToASCII;

architecture RTL of ScanToASCII is

begin

  process (Din)
  begin  -- process

    case Din is
      when "00011100" =>

        Dout <= "1100001";
        
      when "00110010" =>

        Dout <= "1100010";
        
      when "00100001" =>

        Dout <= "1100011";
        
      when "00100011" =>

        Dout <= "1100100";
        
      when "00100100" =>

        Dout <= "1100101";
        
      when "00101011" =>

        Dout <= "1100110";
        
      when "00110100" =>

        Dout <= "1100111";
        
      when "00110011" =>

        Dout <= "1101000";
        
      when "01000011" =>

        Dout <= "1101001";
        
      when "00111011" =>

        Dout <= "1101010";
        
      when "01000010" =>

        Dout <= "1101011";
        
      when "01001011" =>

        Dout <= "1101100";
        
      when "00111010" =>

        Dout <= "1101101";
        
      when "00110001" =>

        Dout <= "1101110";
        
      when "01000100" =>

        Dout <= "1101111";
        
      when "01001101" =>

        Dout <= "1110000";
        
      when "00010101" =>

        Dout <= "1110001";
        
      when "00101101" =>

        Dout <= "1110010";
        
      when "00011011" =>

        Dout <= "1110011";
        
      when "00101100" =>

        Dout <= "1110100";
        
      when "00111100" =>

        Dout <= "1110101";
        
      when "00101010" =>

        Dout <= "1110110";
        
      when "00011101" =>

        Dout <= "1110111";
        
      when "00100010" =>

        Dout <= "1111000";
        
      when "00110101" =>

        Dout <= "1111001";
        
      when "00011010" =>

        Dout <= "1111010";
        
      when others =>

        Dout <= "0000000";

    end case;

  end process;
end RTL;

