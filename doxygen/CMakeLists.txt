# configure doxygen file
configure_file(Doxyfile.in
    Doxyfile)

# create doxygen
add_custom_target(doxygen
    COMMAND doxygen Doxyfile)
