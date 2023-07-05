cmake_minimum_required(VERSION 3.5)

project(InventoryManagement VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# Copy the CSV file to the build directory
configure_file(data.csv ${CMAKE_CURRENT_BINARY_DIR}/data.csv COPYONLY)
configure_file(CurrencyExchangeRates.csv ${CMAKE_CURRENT_BINARY_DIR}/CurrencyExchangeRates.csv COPYONLY)

set(PROJECT_SOURCES
        main.cpp
        GUI/mainwindow.cpp GUI/mainwindow.h GUI/mainwindow.ui
        product.h product.cpp
        user.h user.cpp
        seller.h seller.cpp
        products.h products.cpp
        purchase.h purchase.cpp
        sold.h sold.cpp
        invoiceItem.h invoiceItem.cpp
        invoiceItems.h invoiceItems.cpp
        Invoice.h Invoice.cpp
        resource.qrc
        GUI/customer_signup_page.h GUI/customer_signup_page.cpp GUI/customer_signup_page.ui
        GUI/seller_signup_window.h GUI/seller_signup_window.cpp GUI/seller_signup_window.ui
        GUI/home_window.h GUI/home_window.cpp GUI/home_window.ui
        GUI/inventory_widget.h GUI/inventory_widget.cpp GUI/inventory_widget.ui
        GUI/purchase_widget.h GUI/purchase_widget.cpp GUI/purchase_widget.ui
        GUI/reports_widget.h GUI/reports_widget.cpp GUI/reports_widget.ui
        GUI/currency_widget.h GUI/currency_widget.cpp GUI/currency_widget.ui
        GUI/invoice_widget.h GUI/invoice_widget.cpp GUI/invoice_widget.ui
        datahandler.h datahandler.cpp
        manufacturers.h manufacturers.cpp
        GUI/add_product_window.h GUI/add_product_window.cpp GUI/add_product_window.ui
        GUI/add_to_invoice.h GUI/add_to_invoice.cpp GUI/add_to_invoice.ui
        GUI/edit_product_window.h GUI/edit_product_window.cpp GUI/edit_product_window.ui
        GUI/product_information_window.h GUI/product_information_window.cpp GUI/product_information_window.ui
        CurrencyConverter.h CurrencyConverter.cpp
        Currency.h Currency.cpp
        CurrencyExchangeRates.csv
        GUI/edit_exchange_rate_window.h GUI/edit_exchange_rate_window.cpp GUI/edit_exchange_rate_window.ui
        GUI/purchase_invoice_window.h GUI/purchase_invoice_window.cpp GUI/purchase_invoice_window.ui
        GUI/sale_invoice_window.h GUI/sale_invoice_window.cpp GUI/sale_invoice_window.ui
        dataBase.db
        InvoiceNumbers.h InvoiceNumbers.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(InventoryManagement
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET InventoryManagement APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(InventoryManagement SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(InventoryManagement
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(InventoryManagement PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(InventoryManagement PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS InventoryManagement
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(InventoryManagement)
endif()
