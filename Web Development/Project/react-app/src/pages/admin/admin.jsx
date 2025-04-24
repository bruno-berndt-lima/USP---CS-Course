import React, { useState } from 'react';
import './admin.css';
import Header from '../../components/Header';
import Sidebar from '../../components/Sidebar';
import AdminProducts from './adminProducts';
import AdminUsers from './adminUsers';
import AdminOrders from './adminOrders';
import NotFound from '../notfound/notfound';

const Admin = ({headerUser}) => {
    const [activePage, setActivePage] = useState("/adminProducts");
    
    const handlePageClick = (page) => {
        setActivePage(page);
    } 

    if(headerUser.admin) return (  
        <>
            <Header user={headerUser} logged={headerUser.logged}/>
            <Sidebar activePage={activePage} handlePageClick={handlePageClick} />
            <div className="container-data">
                {activePage === '/adminProducts' && <AdminProducts />}
                {activePage === '/adminUsers' && <AdminUsers />}
                {activePage === '/adminOrders' && <AdminOrders />}           
            </div>
        </>
    );
    else return (<NotFound />);
}
 
export default Admin;