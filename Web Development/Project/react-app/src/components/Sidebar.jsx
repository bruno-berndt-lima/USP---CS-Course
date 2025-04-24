import React from 'react';
import './Sidebar.css';


const Sidebar = ({ activePage, handlePageClick }) => {
    return (
        <div className="sidebar">
            <ul className="sidebar-links">
                <li className={activePage === '/adminProducts' ? 'active' : ''}>
                    <div className="sidebar-link" onClick={() => handlePageClick('/adminProducts')}>
                        Products
                    </div>
                </li>

                <li className={activePage === '/adminUsers' ? 'active' : ''}>
                    <div className="sidebar-link" onClick={() => handlePageClick('/adminUsers')}>
                        Users
                    </div>
                </li>

                <li className={activePage === '/adminOrders' ? 'active' : ''}>
                    <div className="sidebar-link" onClick={() => handlePageClick('/adminOrders')}>
                        Orders
                    </div>
                </li>
                </ul>
        </div>
      );            
  };
  
  export default Sidebar;
