/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @author Christian <c@ethdev.com>
 * @date 2016
 * Full-stack Solidity inline assember.
 */

#pragma once

#include <libsolidity/interface/Exceptions.h>

#include <libjulia/backends/evm/AbstractAssembly.h>

#include <string>
#include <functional>

namespace dev
{
namespace eth
{
class Assembly;
}
namespace solidity
{
class Scanner;
namespace assembly
{
struct Block;
struct Identifier;

class InlineAssemblyStack
{
public:
	/// Parse the given inline assembly chunk starting with `{` and ending with the corresponding `}`.
	/// @return false or error.
	bool parse(
		std::shared_ptr<Scanner> const& _scanner,
		julia::ExternalIdentifierAccess::Resolver const& _externalIdentifierResolver = julia::ExternalIdentifierAccess::Resolver()
	);
	/// Converts the parser result back into a string form (not necessarily the same form
	/// as the source form, but it should parse into the same parsed form again).
	std::string toString();

	eth::Assembly assemble();

	/// Parse and assemble a string in one run - for use in Solidity code generation itself.
	bool parseAndAssemble(
		std::string const& _input,
		eth::Assembly& _assembly,
		julia::ExternalIdentifierAccess const& _identifierAccess = julia::ExternalIdentifierAccess()
	);

	ErrorList const& errors() const { return m_errors; }

private:
	std::shared_ptr<Block> m_parserResult;
	ErrorList m_errors;
};

}
}
}
