import React, { useEffect } from 'react';
import { useNavigate } from 'react-router-dom';

const NotFound = () => {
    const navigate = useNavigate();
    // Pagina basica que redireciona o usuário a home caso digite uma url que não exista no site ou não acessável ao usuário
    useEffect(() => {
        navigate('/');
    })
}
 
export default NotFound;