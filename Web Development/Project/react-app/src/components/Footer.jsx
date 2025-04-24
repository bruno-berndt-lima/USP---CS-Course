import React from 'react';
import { Link } from 'react-router-dom';
import { FaFacebook, FaInstagram, FaTwitter } from 'react-icons/fa';
import './Footer.css';
import '../App.css';



const Footer = () => {
    const logo = 'https://i.imgur.com/pGHQ2zI.png';

    return (  
        <footer className='footer'>
            <div className="column1">
                <Link to='/'>
                    <img className='logo-img' src={logo} alt='logo'></img>
                </Link>          

                <h2>DigitalFit</h2>
                <ul>
                    <li>
                        <a className='instagram-icon' href="https://www.instagram.com/"><FaInstagram /></a>
                    </li>
                    <li>
                        <a className='twitter-icon' href="https://www.twitter.com/"><FaTwitter /></a>
                    </li>
                    <li>
                        <a className='facebook-icon' href="https://www.facebook.com/"><FaFacebook /></a>
                    </li>
                </ul>

            </div>

            <div className="column2">
                <h1>How can we help you? <br/> Get in touch with us.</h1>
                <p>(16) 91234-5678</p>
                <p>digitalfit@gmail.com</p>            
            </div>

            <div className="column3">
                <h1>Quick links</h1>
                <ul>
                    <li><Link to='/'>Visit Store</Link></li>
                    <li><Link to='/'>Let's Connect</Link></li>
                    <li><Link to='/'>Know More About Us</Link></li>
                </ul>
            </div>

            <div className="column4">
                <h1>Important links</h1>
                <ul>
                    <li><Link to='/'>Privacy Policy</Link></li>
                    <li><Link to='/'>Shipping Details</Link></li>
                    <li><Link to='/'>Terms and Conditions</Link></li>
                </ul>
            </div>
        </footer>
    )
}

export default Footer;