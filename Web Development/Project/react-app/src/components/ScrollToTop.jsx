import { useEffect } from "react";
import { useLocation } from "react-router-dom";

// Function to scroll to top of window on change of route
export default function ScrollToTop() {
  const { pathname } = useLocation();

  useEffect(() => {
    window.scrollTo(0, 0);
  }, [pathname]);

  return null;
}