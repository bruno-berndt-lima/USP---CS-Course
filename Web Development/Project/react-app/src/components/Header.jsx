import React, { useRef, useState } from 'react';
import { Link } from 'react-router-dom';
import { FaShoppingCart, FaBars } from 'react-icons/fa';
import './Header.css';
import '../App.css';

const Header = ({user, logged}) => {
    const navRef = useRef();

    // URL da logo do site
    const logo = 'https://i.imgur.com/pGHQ2zI.png';

    // Quando o width da tela chega em determinado tamanho, um ícone de menu sanduíche substitui os botões; ao clicar nesse ícone, um dropdown é mostrado, ao clicar
    // novamente ele se torna invisível
    const showNavBar = () => {
        navRef.current.classList.toggle("show-options");
    }

    const buttonUser = () => {
        if(logged){
            return(<Link className='navbar-link' to={`/user/${user._id}`}>{user.name}</Link>)
        } else {
            return(<Link className='navbar-link' to="/login">Login</Link>)
        }
    }

    const cartIcon = () => {
        if(!user.admin) {
            return(
                <li><Link className='navbar-link navbar-brown' to='/cart'><FaShoppingCart /></Link></li>
            )
        }
    }

    return (  
        <nav className='navbar'>
            <div className="logo">
                <Link to={user.admin ? '/admin' : '/'}>
                    <img className='logo-img-header' src={logo} alt='logo'></img>
                </Link>
            </div>
            <button className='toggle-button' onClick={showNavBar}>
                <FaBars />
            </button>
            <div ref={navRef} className="navbar-links">
                <ul>
                    <li><Link className='navbar-link navbar-brown' to={user.admin ? '/admin' : '/'}>Home</Link></li>
                    <li>{buttonUser()}</li>
                    {cartIcon()}
                </ul>
            </div>
        </nav>
    );
}
 
export default Header;