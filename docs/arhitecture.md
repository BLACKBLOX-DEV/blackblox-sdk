## I2C Addressing and Bus Topology

BLACKBLOX peripheral modules may use DIP switches to configure I2C addresses when supported by the underlying IC or firmware.

The SDK SHALL NOT assume that an I2C address uniquely identifies a module type. The same address may be used by different ICs or BLACKBLOX modules.

Address conflicts SHALL be solved physically or topologically, not by guessing in software.

Future processor modules may expose separate BLACKBLOX I2C buses per cube side. This can reduce bus capacitance, shorten physical bus segments and simplify address conflict resolution.

Future BLACKBLOX multiplexer modules may be used to connect multiple devices with identical I2C addresses.

The basic I2C scanner SHALL only report responding addresses. It SHALL NOT attempt to identify device types unless a specific identification protocol is supported by the target module.