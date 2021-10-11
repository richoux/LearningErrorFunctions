/*
 * GHOST (General meta-Heuristic Optimization Solving Tool) is a C++ library 
 * designed to help developers to model and implement optimization problem 
 * solving. It contains a meta-heuristic solver aiming to solve any kind of 
 * combinatorial and optimization real-time problems represented by a CSP/COP/CFN. 
 *
 * GHOST has been first developped to help making AI for the RTS game
 * StarCraft: Brood war, but can be used for any kind of applications where 
 * solving combinatorial and optimization problems within some tenth of 
 * milliseconds is needed. It is a generalization of the Wall-in project.
 * Please visit https://github.com/richoux/GHOST for further information.
 * 
 * Copyright (C) 2014-2021 Florian Richoux
 *
 * This file is part of GHOST.
 * GHOST is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as published 
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * GHOST is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with GHOST. If not, see http://www.gnu.org/licenses/.
 */


#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "thirdparty/randutils.hpp"

namespace ghost
{
	//! This class encodes variables of your model. You cannot inherits your own class from Variable.
	/*! 
	 * In GHOST, all variables are discrete variables with a domain containing integers only 
	 * (positive, negative or both). Since you cannot inherits from Variable, if your constraints 
	 * or your objective function need specific details about your variables (for instance, each variable models 
	 * an agent with 2D coordinates), you must store these data on your own containers side by side with 
	 * the variables vector (see Constraint and Objective).
	 *
	 * While modeling your problem with GHOST, make sure you understand the difference between your variable values 
	 * (stored in the variable's domain) and your variable additional data (such as 2D coordinates for instance). 
	 * You must manage additional data with your own data structures or classes.
	 *
	 * \sa Constraint Objective
	 */
	class Variable final
	{
		friend class SearchUnit;

		std::string _name;	//!< String to give a name to the variable, helpful to debug/trace.
		std::vector<int> _domain; //!< The domain, i.e., the vector of values the variable can take.
		int _id; //!< Unique ID integer

		int	_current_value;	// Current value assigned to the variable.
		int _min_value; // minimal value in the domain
		int _max_value; // maximal value in the domain
		randutils::mt19937_rng _rng; 	// Neat random generator implemented in thirdparty/randutils.hpp, see https://www.pcg-random.org/posts/ease-of-use-without-loss-of-power.html
				
		struct valueException : std::exception
		{
			int value;
			int min;
			int max;
			valueException( int value, int min, int max ) : value( value ), min( min ), max( max ) {}
			std::string message = "Wrong value " + std::to_string( value ) + " passed to Variable::set_value. The given value does not belong to the domain and/or is not be between "
				+ std::to_string( min ) + " (included) and "
				+ std::to_string( max ) + " (included).\n";
			const char* what() const noexcept { return message.c_str(); }
		};

		// Assign to the variable a random values from its domain.
		inline void pick_random_value()	{	_current_value = _rng.pick( _domain ); }
		
	public:
		Variable() = default;		
		
		//! First Variable constructor, with the vector of domain values and the outside-the-scope value.
		/*!
		 * \param name A const reference of a string to give a full name to the variable (for instance, "Barracks").
		 * \param domain A const reference to the vector of integers composing the domain to create.
		 * \param index The domain's index corresponding to the variable initial value. Zero by default.
		 */
		Variable( const std::string&	name,
		          const std::vector<int>& domain,
		          int	index = 0 );
    
		//! Second Variable constructor, with a starting value and a size for the domain.
		/*!
		 * \param name A const reference of a string to give a full name to the variable (for instance, "Barracks").
		 * \param startValue An integer representing the first value of the domain. The creating domain will then be the interval [startValue, startValue + size].
		 * \param size A size_t corresponding to the size of the domain to create.
		 * \param index The domain's index corresponding to the variable initial value. Zero by default.
		 */
		Variable( const std::string&	name,
		          int	startValue,
		          std::size_t size,
		          int	index = 0 );
    
		/*! Inline method returning all values in the domain.
		 * \return a copy of the vector of these values.
		 */
		inline std::vector<int> get_full_domain() const { return _domain; }

		/*! Method returning a range of values from the domain.
		 * \return a copy of the vector of these values.
		 */
		std::vector<int> get_partial_domain( int range ) const;

		//! Inline method to get the current value of the variable.
		/*! 
		 * \return An integer corresponding to the variable value. 
		 */
		inline int get_value() const { return _current_value; }

		//! Set the value of the variable.
		/*!
		 * If the given value is not in the domain, raises a valueException.
		*/
		inline void	set_value( int value )
		{
			if( std::find( _domain.cbegin(), _domain.cend(), value ) == _domain.cend() )
				throw valueException( value, get_domain_min_value(), get_domain_max_value() );
			
			_current_value = value;
		}

		//! Inline method returning the size of the domain of the variable.
		/*! 
		 * \return a size_t equals to size of the domain of the variable.
		 */
		inline std::size_t get_domain_size() const { return _domain.size(); }

		//! Inline method returning the minimal value in the variable's domain.
		/*! 
		 * \return the minimal value in the variable's domain.
		 */
		inline int get_domain_min_value() const { return _min_value; }

		//! Inline method returning the maximal value in the variable's domain.
		/*! 
		 * \return the maximal value in the variable's domain.
		 */
		inline int get_domain_max_value() const { return _max_value; }

		//! Inline method to get the variable name.
		inline std::string get_name() const { return _name; }

		//! Give the unique id of the Variable object.
		inline int get_id() const { return _id; }

		//! To have a nicer stream of Variable.
		friend std::ostream& operator<<( std::ostream& os, const Variable& v )
		{
			std::string domain = "";
			for( auto value : v.get_full_domain() )
				domain += std::to_string( value ) + std::string( ", " );
				// domain << value << ", ";
			
			return os
				<< "Variable name: " << v._name
				<< "\nId: " <<  v._id
				<< "\nValue: " <<  v._current_value
				<< "\nDomain: " << domain
				<< "\n--------";
		}
	};
}
