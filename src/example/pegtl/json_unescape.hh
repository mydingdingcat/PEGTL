// Copyright (c) 2014-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAOCPP_PEGTL_INCLUDE_EXAMPLES_JSON_UNESCAPE_HH
#define TAOCPP_PEGTL_INCLUDE_EXAMPLES_JSON_UNESCAPE_HH

#include <string>

#include <tao/pegtl.hh>
#include <tao/pegtl/contrib/json.hh>
#include <tao/pegtl/contrib/unescape.hh>

namespace examples
{
   // State base class to store an unescaped string

   struct unescape_state_base
   {
      unescape_state_base() = default;

      unescape_state_base( const unescape_state_base & ) = delete;
      void operator= ( const unescape_state_base & ) = delete;

      std::string unescaped;
   };

   // Action class for parsing literal strings, uses the PEGTL unescape utilities, cf. unescape.cc.

   template< typename Rule, template< typename ... > class Base = tao::TAOCPP_PEGTL_NAMESPACE::nothing >
   struct unescape_action : Base< Rule > {};

   template<> struct unescape_action< tao::TAOCPP_PEGTL_NAMESPACE::json::unicode > : tao::TAOCPP_PEGTL_NAMESPACE::unescape::unescape_j {};
   template<> struct unescape_action< tao::TAOCPP_PEGTL_NAMESPACE::json::escaped_char > : tao::TAOCPP_PEGTL_NAMESPACE::unescape::unescape_c< tao::TAOCPP_PEGTL_NAMESPACE::json::escaped_char, '"', '\\', '/', '\b', '\f', '\n', '\r', '\t' > {};
   template<> struct unescape_action< tao::TAOCPP_PEGTL_NAMESPACE::json::unescaped > : tao::TAOCPP_PEGTL_NAMESPACE::unescape::append_all {};

} // examples

#endif