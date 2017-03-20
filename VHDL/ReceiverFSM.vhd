library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;  

entity ReceiverFSM is

  port (
    PS2ClkPulse : in  std_logic;
    PS2Data     : in  std_logic;
    ParityOK    : in  std_logic;
    Clk, Reset  : in  std_logic;
    Shift_en    : out std_logic;
    FifoWrite   : out std_logic);

end ReceiverFSM;
architecture FSMMachine of ReceiverFSM is
  -- states of the machine
 constant Idle : std_logic_vector(3 downto 0) := "0000";
 constant S0 : std_logic_vector(3 downto 0) := "0001";
 constant S1 : std_logic_vector(3 downto 0) := "0010";
 constant S2 : std_logic_vector(3 downto 0) := "0011";
 constant S3 : std_logic_vector(3 downto 0) := "0100";
 constant S4 : std_logic_vector(3 downto 0) := "0101";
 constant S5 : std_logic_vector(3 downto 0) := "0110";
 constant S6 : std_logic_vector(3 downto 0) := "0111";
 constant S7 : std_logic_vector(3 downto 0) := "1000";
 constant Parity : std_logic_vector(3 downto 0) := "1001";
 constant StopBit : std_logic_vector(3 downto 0) := "1010";

begin
   
   nexts: process (PS2ClkPulse,Clk,Reset,PS2Data,ParityOK)
 variable actualState,nextState : std_logic_vector(3 downto 0) := "0000";  -- inicially all in IDLE
   begin  -- process next
     if (Reset ='1')  then
       actualState := Idle;
       nextState := Idle;
       Shift_en <= '0';
       FifoWrite <= '0';
     elsif rising_edge(Clk) then
       actualState := nextState; 

       case actualState is
         when Idle =>
           if PS2ClkPulse = '1' and PS2Data = '0' then  -- the start bit (0);
           nextState := S0;
           else
             nextState := Idle;
         end if;
             Shift_en <= '0';
             FifoWrite <= '0';
         when S0 => if PS2ClkPulse = '1' then
           nextState := S1;
           Shift_en <= '1';
           else
             nextState := S0;
             Shift_en <= '0';
           end if;
             FifoWrite <= '0';
            
         when S1 => if PS2ClkPulse = '1' then
           nextState := S2;
           Shift_en <= '1';
           else
             nextState := S1;
             Shift_en <= '0';
           end if;
             FifoWrite <= '0';


        when S2 => if PS2ClkPulse = '1' then
           nextState := S3;
           Shift_en <= '1';
           else
             nextState := S2;
             Shift_en <= '0';
           end if;
             FifoWrite <= '0';


        when S3 => if PS2ClkPulse = '1' then
           nextState := S4;
           Shift_en <= '1';
           else
             nextState := S3;
             Shift_en <= '0';
           end if;
             FifoWrite <= '0';           



       when S4 => if PS2ClkPulse = '1' then
           nextState := S5;
           Shift_en <= '1';
           else
             nextState := S4;
             Shift_en <= '0';
           end if;
             FifoWrite <= '0';


       when S5 => if PS2ClkPulse = '1' then
           nextState := S6;
           Shift_en <= '1';
           else
             nextState := S5;
             Shift_en <= '0';
           end if;
             FifoWrite <= '0';

       when S6 => if PS2ClkPulse = '1' then
           nextState := S7;
           Shift_en <= '1';
           else
             nextState := S6;
             Shift_en <= '0';
           end if;
             FifoWrite <= '0';           

      when S7 => if PS2ClkPulse = '1' then
           nextState := Parity;
           Shift_en <= '1';
           else
             nextState := S7;
             Shift_en <= '0';
           end if;
             FifoWrite <= '0';

      when Parity => if PS2ClkPulse = '1' then
           nextState := StopBit;
           Shift_en <= '1';
           else
             nextState := Parity;
             Shift_en <= '0';
           end if;
             FifoWrite <= '0';

       when StopBit => if PS2ClkPulse = '1' then
           nextState := Idle;
          if PS2Data = '1' then
           if ParityOK = '1' then   --am I suppose to consider Stop bit after the last
                                                      --one of the 8 bits data?
             FifoWrite <= '1';
           else
             FifoWrite <= '0';
           end if;
              else
             FifoWrite <= '0';
           end if;
         
       else
         nextState := StopBit;
         FifoWrite <= '0';
       end if;
       Shift_en <= '0';
         when others =>
         null;
     end case;
     end if;
     
   end process nexts;
end FSMMachine;


