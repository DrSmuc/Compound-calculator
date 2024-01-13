# compound-calculator
 Calculates the percentage of elements in the compound

Input data:<br>
 - **"files" -> input.txt** - write formulas<br>

Example:<br>
NaPb2(CO3)2(OH)<br>
NiC31H32N4<br>
K(UO2)(AsO4)·3H2O<br>
Sn2+21O6(OH)14Cl16<br>
.<br>
.<br>
.<br>

Output:<br>
 - **"files" -> output.txt**<br>
 - copy contents into Excel document<br>

Fileter specific element:<br>
 - if chosen, that element will appear in the first collumn if it exists in firmula<br>
 - simbol of the element and "%" won't be displayed<br>
 - **"skip"** to not use feature<br>

Excludes undefined formulas:<br>
 - (NH<sub>4</sub>,K,Pb,Na)<sub>9</sub>Fe<sup>2+</sup><sub>4</sub>(SO<sub>4</sub>)5C<sub>18</sub> inludding ","<br>
 - Al<sub>2</sub>O<sub>3</sub>(SiO<sub>2</sub>)<sub>**1.3-2.0**</sub>·**2.5-3.0**H<sub>2</sub>O including "-"<br>
 - SiO<sub>2</sub>·**n**C<sub>**x**</sub>H<sub>**2x+2**</sub> including "n" or "x"<br>
 - (Pb,**REE**,Ca)Cu<sub>6</sub>(AsO<sub>4</sub>)<sub>3</sub>(OH)<sub>6</sub>·3H<sub>2</sub>O including "REE"<br>

### Incorect result if:<br>
 - "·xH2O" is not et the end or anything other than H2O<br>
