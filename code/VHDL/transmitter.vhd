library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Transmitter is
  
  port (
    din       : in  std_logic_vector(6 downto 0);
    doutS     : out std_logic;
    CLK       : in  std_logic;
    reset     : in  std_logic;
    dataReady : in  std_logic;
    sent      : out std_logic
    );

end Transmitter;

architecture RTL of Transmitter is
type state_type is (IDLE,SBIT,S0,S1,S2,S3,S4,S5,S6,STOPBIT);
signal current_state : state_type;
signal Reg : std_logic_vector(6 downto 0);

begin  -- RTL
  
 P1:   process(CLK,reset,current_state,din,dataReady)
      variable i : integer range 0 to 174 ;    
     
  
 begin  -- process
     if reset = '1' then
       i := 0;
       current_state <= IDLE;
       sent <='0';
        elsif rising_edge(CLK) then
         sent <= '0'; 
         case current_state  is
         when IDLE  =>
           DoutS <= '1';
           if dataReady = '1'  then
           Reg <= din;
           i := 0;  
           current_state <= SBIT;
          
                 
             else
              
             current_state <= IDLE;
            
         end if;

         when SBIT =>
            
             DoutS <= '0';
               if i = 174 then
           i := 0 ;
           current_state <= S0;
               else
               i := i +1;  
               current_state <= SBIT;
               end if;

         when S0 =>
               
                DoutS <= Reg(0);
                
                if i = 174 then
                 i := 0 ;
                  Reg(6 downto 0) <= '0' & Reg(6 downto 1);
               
                current_state <= S1;
              else
                i := i +1; 
                current_state <= S0;
              end if;
              

          when S1 =>
                DoutS <= Reg(0);
               
           
                if i = 174 then
                 i := 0 ;
                  Reg(6 downto 0) <= '0' & Reg(6 downto 1);
                
                current_state <= S2;
               else
                current_state <= S1;
                i := i +1;
              end if;
                
           when S2 =>
               DoutS <= Reg(0);
                
               if i = 174 then
                 i := 0 ;
                 Reg(6 downto 0) <= '0' & Reg(6 downto 1);
               
                current_state <= S3;
               else
                current_state <= S2;
                i := i+1;
              end if;    
                
            when S3 =>
               DoutS <= Reg(0);
               
               if i = 174 then
                i := 0 ;
                 Reg(6 downto 0) <= '0' & Reg(6 downto 1);
                
                current_state <= S4;
                else
                current_state <= S3;
                i := i +1;
              end if;
               
             when S4 =>
                DoutS <= Reg(0);
                
               if i = 174 then
                i := 0 ;
                Reg(6 downto 0) <= '0' & Reg(6 downto 1);
                current_state <= S5;
                else
                current_state <= S4;
                i := i + 1;
              end if;
               
              when S5 =>
               DoutS <= Reg(0);
               
               if i = 174 then
                 i := 0 ;
                 Reg(6 downto 0) <= '0' & Reg(6 downto 1);
                current_state <= S6;
                else
                current_state <= S5;
                i := i +1;
              end if;
               
               when S6 =>
                DoutS <= Reg(0);
                
               if i = 174 then
                 i := 0 ;
                 Reg(6 downto 0) <= '0' & Reg(6 downto 1);
                 current_state <= StopBit;
                else
                current_state <= S6;
                i := i +1;
              end if;
               
               
                when STOPBIT =>
                  DoutS <= '1';
               if i = 174 then
                  i := 0 ;
                  
                   current_state <= IDLE;
                   sent <= '1';
                else
                   current_state <= STOPBIT;
                   i := i +1;
                  end if;  
                    
         when others => null;
       end case;
                end if;
                end process;
                  
 
end RTL;
