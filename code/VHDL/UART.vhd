library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity UART is
port(
    reset         : in std_logic;
    CLK           : in std_logic;
    Ren_UART      : in std_logic;
    Wen_UART      : in std_logic;
    doutS         : out std_logic;
    Addr_UART     : in std_logic_vector(31 downto 0);
    Data_FromUART : out  std_logic_vector(31 downto 0);
    Data_ToUART   : in std_logic_vector(31 downto 0)
    );  

end UART;
 
  architecture RTL of UART is

      signal controlreg : std_logic_vector(31 downto 0);
        signal datareg : std_logic_vector(31 downto 0);
        signal ready : std_logic;
        signal sent_sig : std_logic;
      component transmitter
       port (
    din       : in  std_logic_vector(6 downto 0);
    doutS     : out std_logic;
    CLK       : in  std_logic;
    reset     : in  std_logic;
    dataReady : in  std_logic;
    sent      : out std_logic  
     );
      end component transmitter;

     
         begin  -- RTL
transmitter_1:transmitter 
 port map (
    din       => datareg(6 downto 0),
    doutS     => doutS,
    CLK       => CLK,
    reset     => reset,
    dataReady => ready,
    sent      => sent_sig  
     );

        process (CLK,reset)
           
           begin

                if reset = '1' then
                controlreg <= (0 =>'1' ,others => '0');  --the uart ready to
                                                         --receive data
                datareg <= (others => '0');
                Data_FromUART <= (others => '0');
             elsif rising_edge(CLK) then
                  ready <='0'; 
                  if Ren_UART = '1' then
                     if Addr_UART = x"FFFF0008" then
                        Data_FromUART <= controlreg;
                     elsif Addr_UART = x"FFFF000C" then
                        Data_FromUART <= datareg;
                       end if;
                   end if;        
                  if Wen_UART = '1' then
                      if Addr_UART = x"FFFF000C" then
                         if controlreg(0) = '1' then
                             datareg <= Data_ToUART;
                             controlreg(0) <= '0';
                             ready <= '1';  
                           end if;
                       end if;       
                      end if;           
                    end if;
                        if sent_sig = '1' then  -- the transmitter is done
                                                -- sending the charecter
                          ready <= '0';           
                          controlreg(0) <= '1';  -- ready to take another char
                                                 -- to the data register
                        end if;
                    end process;     
                     
                 

    

  end RTL;
