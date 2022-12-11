library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ParityChecker is

  port (
    D  : in  std_logic_vector(8 downto 0);
    OK : out std_logic);

end ParityChecker;

architecture RTL of ParityChecker is

begin  -- RTL

  process (D)

  begin  -- process
    OK <= D(8) xor D(7) xor D(6) xor D(5) xor D(4) xor D(3) xor D(2) xor D(1) xor D(0);
  end process;

end RTL;
