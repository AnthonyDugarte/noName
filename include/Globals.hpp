# define GLOBALS_HPP

namespace Globals
{
  // niveles de alpha para las colisiones.
  // A partir del punto especificado, los objetos no tendrán colisión con dichos elementos.


  // *  El mapa tendrá un suelo de: 230, el valor más bajo de colisión.
  // *  Los obstáculos de mapa tendrán un valor de:  253, esto para evitar que las balas
  //  exploten con ellos.
  //  * los muros, zona no pasable, tendrán un valor del estandar: 255,
  //   si se introducen unidades aéreas, este valor se reducirá a: 254.

  constexpr short unsigned mapGround { 231u };
  constexpr short unsigned mapObjects { 254u };

  //  * Los cuerpos de las unidades tendrán un valor de: 241.
  //  * Los pies tendrán un valor de 245.
  constexpr short unsigned unitbody { 241u };
  constexpr short unsigned unitfeet { 245u };

  //  * Las zonas que ocasionan daño, tendrán el valor de: 240, pudiend así ocaasionar daños
  //  en el cuerpo y los pies de las unidades.
};
