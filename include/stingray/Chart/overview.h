///////////////////////////////////////////////////////////////////////////////
// overview.h
//
// Copyright (c) 1999-2009 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

//@doc


//@topic SRGraphLabel Class Overview |  
//Based upon the standard component class this component provides a powerful labeling feature to the Objective Chart kit.
//A single line of text may be displayed in any font and in any position on screen. Furthermore the text can be rotated into any orientation. This basic labeling component also has features built in to allow it to move in a pre-programmed direction in case of overlap with other labels.
//
//Unlike the standard Windows text output system which always outputs text in relation to the top left hand corner of a line, the SRGraphLabel component has a location point system which allows the label to be positioned in relation to one of nine points. These points are situated at all four corners, in the centers of the four sides and in the very center of the label.
//
//A label has a background, border and shadow feature just like the standard component. However if a label is oriented at 45 degrees from the normal horizontal base line the panel which it is placed upon will also be rotated, the edges lighted and the shadow placed in the correct relative positions.
//
//Each label has a movement vector associated with it. This vector can be programmed to point in a particular direction. When the label is used as a member of a label block the SRGraphLabelBlock::Draw routine which handles the final output of the individual labels may detect the label overlapping another. When this occurs the label may either be removed or shifted in the direction dictated by the movement vector. In this way labels will never overlap.
//Note that separate and individual labels have no self-vectoring ability.

//@topic SRGraphLabelBlock Class Overview | 
//The SRGraphLabelBlock is a class which contains and manages a variable length linked list of SRGraphLabel objects.
//
//The position and orientation of a block of labels is defined by the m_ptStart and m_ptEnd members. These CPoint objects are the end points of an imaginary line along which the labels may be placed at set intervals. A member function SRGraphLabelBlock::SetBlockPositions will automatically position any labels contained in the block along that line. Furthermore if that line is not perpendicular to the screen x or y axes then the labels will be rotated to an angle which will place them perpendicular to the line drawn between the two anchor points.
//
//In any given list of labels the situation may arise where the text of one label will overlap the text of another. To reduce or eliminate this problem a label block has the ability to remove or displace labels. In the case of simple label blocks the labels which overlap are removed from view but not removed from the list. This means for example that if the block is being used to annotate a graph axis which is zoomed out, zooming in on the axis will reveal more detail and in turn more labels.
//The anti collision system will also move labels on a pre-programmed vector until they no longer overprint their neighbours. Vectors may be set to all be in the same direction in which case the label list will progressively stagger the labels in neat tiers of two then three or more rows. Vectors may also be set in any arbitrary direction in which case the label will simply wander off until it no longer interferes with another.
//An example of this is the pie chart label block which gives each label a vector consistent with the angle described from the centre of the pie through the centre of the wedge and on out into the space beyond.
//
//To facilitate the generation of tick marks and grid-lines which are positioned accurately next to the labels the SRGraphLabelBlock can automatically fill an array of CPoint objects with the positions of its labels as the draw cycle progresses. This array may then be used to draw the ticks and grids exactly at the position of the labels.
//
//As a label block is drawn, all the extents of all the labels are accumulated into a rectangle. The sizes of this rectangle can be used to move other items, like the m_DisplayRect dimensions, so that axis and data do not overprint the labels.
//To better calculate the positions and sizes a two pass system is employed. It is true that when a graph is being drawn the labels will eat away at the available surface area which the display can use. This may in turn mean that a reduced display area will further diminish the space available to labels by shortening the length of the axes. To prevent a catch 22 deadlocking the labels can be told to draw a "pass 0" or "pass 1" set.
//Pass 0 will perform all the calculations and return an estimated size without actually placing text on the screen. Pass 1 will also perform calculations but will have already taken into account the reduction in display area which they themselves have caused. Any minor label collisions which take place in pass 1 will be much less noticeable.
//
//SRGraphLabelBlock, even though it draws the labels themselves as true components with panels, borders and shadows, will not draw such items for itself. Furthermore the labels are normally text only and do not have the normal component aesthetics turned on. If you want to see panels you may program each individual label to show its own panel or you can place the label list on top of a dummy SRGraphBackground panel.

//@topic SRGraphPosition Class Overview | 
//The SRGraphPosition class is a communication class which interrogates the graphs data and component structures and returns information regarding them based upon the x,y coordinate position supplied. Very often this coordinate will be the direct input from the mouse or other pointer device.
//
//Once a graph position object has been constructed it will look at the graph data and the components in the m_ComponentList member of the parent graph to ascertain exactly where the point was in relation to data and displays. Information is returned via the SRGraphPosition internal data members which must be interrogated according to strict rules.
//The SRGraphPosition class will set certain flags internally and you must read those flags using the provided member functions. For example if the user clicks a mouse button in a display you can use SRGraphPosition to find out what index and what group is being displayed at the point in question. You can ascertain also its numerical value along the X and Y axes. You can also discover what kind of selection can be made if the user is beginning a drag-box selection procedure.
//
//After the initial construction which should be done using the special constructor overload you may ask what data is available. The routine HasIndex() will return TRUE only if an index was successfully calculated from the point. If the answer was TRUE then the index can be retrieved using the GetIndex function.. Similarly there are HasGroup(), HasValueX() and HasValueY() member functions and complimentary get and set functions for all the relavent data members.
//
//A selection type is returned which is different according to the graph type available. The standard type are horizontal, for ordinary x,y classic charts. Vertical for the horizontal bar types, Both for scatter graphs which may have an arbitrary  rectangular selection for zooming and Circular for web charts. Because the process may be working on one of your own graph types a routine is also provided which allows your virtual override of the custom type routine to enter a selection type suitable for your own graph.
//
//Because graph displays may be made to overlay one another transparently the SRGraphPosition class holds a special pointer variable which serves a dual purpose. If the mouse point is found to be in a single SRGraphDisplay objects visible scope then the pointer will be directed at the object in question. This means that supplementary data may be gained by interrogating the display item itself 
//If however the point is found to be in more than one display object a list of the displays is created and the individual displays within that list may be examined by de referencing them with a zero based index. In this case the pointer will be directed to a CPtrList object that can be manipulated in the normal way should it be required.
//An error checked routine is provided to retrieve either the list or the single pointer.
//
//Because the automatic positioning and scaling systems in SRGraph are so complex and dynamic you can never really guarantee to be in a specific place in the data structures until all activity has stopped. Luckily the activity within SRGraph and its components takes place almost exclusively at draw time. After the drawing is finished the components have the "stain" of all the automatic positioning and dynamic movement left intact. Therefore SRGraphPosition can use the m_DisplayRect member in a display component to ascertain the exact position, scale and state of the graphs data. The use of SRGraphPosition during a draw cycle is a pointless waste of time and while it will not crash the computer or destroy data it will not return accurate results.
//
//The accuracy of positioning and data value gathering in SRGraph and by SRGraphPosition is mainly dependant on the screen resolution and the size of the graph data panel being interrogated. If the range of data values goes from 0 to 10,000 and the m_DisplayRect final size is 200 pixels high after the draw cycle finishes then the position accuracy will only be able to deliver a value within 50 units of the real value. Likewise if the number of data items is more than the number of pixels across the m_DisplayRect member then it will not be possible to pick out a single group or index from the position of the mouse.

//@topic CScale Class Overview | 
//CScale is a utility class which allows accumulation of maximum and minimum values.
//
//Used in graph scaling and in the hi-lo history recording system CScale uses an overloaded += operator to compare a value with the maximum and minimum stored values. If value being added to the CScale object is above the maximum or below the minimum then it will become the new value
//
//CScale is mostly used in the drawing and scaling of data. The SRGraphDisplay class will scan all data in a graph adding the values one-by-one into CScale. This maximum and minimum value is then used to decide the best scale for the axes and data.
//
//Several operators are provided to make use of the class simple. They are:
//
// += operators which take int, float, double, char, unsigned int and unsigned char parameters.
// = (assignment) operator for copying one CScale to another.
//
 
//@topic SRDynamicGraph Class Overview | 
//Derived from SRGraph, this class stores data in a directly accessible memory buffer instead of an array of SRGraphData objects. This gives SRDynamicGraph a quicker turn around time than SRGraph and is useful for storing data which is streamed in at a relatively high speed. For instance in data logging applications.
//
//SRDynamicGraph is not intended as a general purpose tool but as a faster alternative to SRGraph for time sensitive data gathering.
//
//Both SRGraph and SRDynamicGraph can be used to implement the Dynamic Data Storage model. SRDynamicGraph expects all data groups to be Dynamic.  With SRGraph, Standard and Dynamic groups can be mixed.
//
//In previous versions of Objective Chart, the Dynamic storage buffers had to be explicitly created and initialized. In OC 6.03 and later, OC can perform this initialization automatically.
//This means that an existing chart setup can be converted from the Standard model to the Dynamic model by simply changing the chart object from SRGraph to SRDynamicGraph -- or by selecting a SRGDynamicDataManager into the SRGraph.
//Override SRGDynamicDataManager::NewGroup() to instantiate a custom SRGraphDynamicData class or to change the default buffer size, etc.
//For example, SRGraphDynamicData::GetAnnotation() is commonly overridden to return text dependent on the current index.

//@topic SRGraph Class Overview | 
//SRGraph is the main class within which all other Objective Chart functions and data storage tasks are wrapped.
//
//Because of the connection between Objective Chart and Objective Grid data storage methods within Objective Chart have been designed to approximate the two dimensional array's used in grid and spreadsheet applications.
//
//SRGraph holds several data arrays. 
//
// The first m_data is a CPtrList object which keeps a list of SRGraphDataList objects. This list can be thought of as the ROW edge cells in the spreadsheet. Each item on the list is the header for a complete row of cells. Columns and in particular the data cells are the SRGraphData objects held in the lists.
//
// Begining with the version, this m_data member is moved into another class SRGDataManager. All the data management is put into the SRGDataManager class. However, it is still backward compatible. All you have to do is to create a SRGDataManager object and pass it to the SRGraph instance before you start put or get the data into the graph. 
// The advantage of this separation is that several SRGraph instances can now share the SRGDataManager object. If application use the SRGraph object to setup the data, the data is in fact still stored into the including SRGDataManager object. So it is hight recommended that application use the SRGDataManager object to setup the data for
// the graph. When a SRGDataManager object is passed to the SRGraph object, application should indicating how the memory of the SRGDataManager object will be freed. During the serialization of SRGraph there is also a decision application has to make, i.e., whether the graph object should serialize the SRGDataManager object internally or
// the SRGDataManager object will be serialized outside the SRGraph object.
//
//As well as storing data the SRGraph class also stores the visual appearance of the graph as a list of SRGraphComponent based objects in the m_ComponentList member. An interesting feature of SRGraph and the Objective Chart system in general is that it does not have a dedicated CWnd based class in which to display the chart data. A simple window used in the application is used as a drawing surface thereby allowing graph and chart displays to be drawn anywhere. In dialogs, on buttons even in a grid-cell itself.
//
//The SRGraph class also provides a specialised feedback system through the m_FeedbackList member. As objects are drawn on the graph. For example a pie wedge in a pie chart, the area covered by that wedge may be optionally logged by SRGraph. Once the drawing process has finished a complete list of areas covered by data representations is available. This list can then be interrogated by using the screen coordinates, perhaps a data cursor or the mouse, and information about the data retrieved in the form of an SRGraphFeedback object.

//@topic SRGDataManager Class Overview | 
//This class handles all the data management of SRGraph. It has a CPtrList object which keeps a list of SRGraphDataList objects. This list of list struture can thought of as a virtual 2-dimensional array of data objects like a spreadsheet of cell. Each row of the 2-dimensional array is a SRGraphDataList object. 
//
//@topic SRGDynamicDataManager Class Overview |
//This class is derived from SRGDataManager specialized to use the Dynamic Data Storage model.
//Selecting a SRGDynamicDataManager-based class into an SRGraph object is the most flexible way to convert easily to using Dynamic data.
//Override SRGDynamicDataManager::NewGroup() to instantiate a custom SRGraphDynamicData class or to change the default buffer size, etc.
//For example, SRGraphDynamicData::GetAnnotation() is commonly overridden to return text dependent on the current index.
//This creates sensible axis labels for Classic axes.

//@topic SRGraphAnnotation Class Overview | 
//Generally every item of data in an Objective Chart application holds an SRGraphAnnotation object. (The exception is SRGraphDynamicData items)This class allows the storage of a string of text to be used as annotation for the data. These annotations are tagged with an integer numeric code. While this code has no fixed significance it is considered as the country code of the language in which the annotation is written. 
//Any data stored in SRGraphData and the headers stored in SRGraphDataList may have any number of strings associated with them. These strings, stored in SRGraphAnnotationList objects can be used to swap languages instantly while keeping the same graphics and data.

//@topic SRGraphAnnotationList Class Overview | 
//SRGraphAnnotationList holds a list of SRGraphAnnotation objects. This variable sized list of text annotations can be used to provide many different text values for the same data item thereby allowing a chart to swap languages or change the meaning of a data item instantly without affecting the data itself.

//@topic SRGraphComponent Class Overview | 
//This is the basic class which manages the display of backgrounds, displays, legends, titles and other items.
//
//The basic SRGraphComponent has the ability to fill its own background, Draw a border around itself and to draw a shadow which reduces the brilliance of items below and to the right of it.
//Background filling may be a solid, single color. A wash or vignette of color's or an image taken from the application resources.
//Borders drawn on the object may be thick or thin (3 pixels or 6 pixels), have the appearance of being raised or lowered or be bevelled in a manner similar to the style used for buttons in Windows.
//Shadows may be thin, medium or thick. They use a checkerboard image to allow only 50 percent of the underlying color to show through.
//SRGraphComponent plays the biggest role in the definition of appearance in Objective Chart. As a basis for your own graph style it can be used to draw bars, lines, 3D bars wigets and polygons all in a style consistent with the original implementations.
//All components have a basic set of variables which allow interaction with and data gathering from the graph which owns the component and also allows certain information to be gleaned about the type of display surface which is being used to draw the component.
//
//The primary channel for graph information is via the m_pParentGraph pointer which must be set to point to the SRGraph object upon whose component list this object is stored. Normally the initialisation of the m_pParentGraph pointer is done when the item is added using the SRGraph::AddComponent function. However some component items may build and use temporary components during their draw cycles. For example an SRGraphDisplay may possibly make a temporary SRGraphLabelBlock in which to store annotations while display is taking place In this case the component which is built on the stack must be informed of the parent graph by using the SetParent member function. Care must be taken to do this at an early stage in the use of the component because the component may fail through lack of important, globally available data held in the parent graph. (i.e. the country code for annotations) Furthermore certain calculations made by the component depend upon knowledge of the CDC and CWnd which is being used to display the item. Under normal circumstances components only do these calculations whilst they are being drawn and will have been informed of the CDC and CWnd by the DrawComponentList member of SRGraph. If however the component is temporary it will not be on the component list and therefore will require that the function class or program which invoked it also tell it what CDC and CWnd is currently in use. To do this the DrawingUsing(CDC *,CWnd *) function is provided.
//
//All components may be provided with a rectangular scope or range of data upon which they should act. The default scope is -1,-1,-1,-1 (Note do not confuse scope with screen size and position) The numbers correspond to the minimum and maximum group and index which the component takes notice of within the two dimensional data structure which holds the graph data. the m_nMinGroup, m_nMaxGroup, m_nMinIndex and m_nMaxIndex members define this scope. A -1 in any of these members makes the scope for that particular item default to the group-index maxima or minima.

//@topic SRGraphData Class Overview | 
//SRGraphData is the class which corresponds to the grid cell in a spreadsheet or grid. It contains three separate types of data. The instantaneous value of the data , the maximum and minimum historic value that the values have been and the text which is associated with this data.
//The value is a simple double. The history is a CScale object and the text is held in an SRGraphAnnotationList

//@topic SRGraphDataList Class Overview | 
//The SRGraphDataList is effectively the row header of the grid. Is holds a list of SRGraphData items each of which corresponds to the individual cells in the row. One for each column. 
//The list also holds an SRGraphAnnotationList object which serves to hold the text corresponding to the row header.

//@topic SRGraphDisplay Class Overview | 
//Based upon SRGraphComponent this class is responsible for drawing the graph itself. It uses the data stored in its parent SRGraph object to draw labels, axes and data. It inherits from its base class the ability to fill its background, draw a border and cast a shadow.
//
//Each component may use the whole of the data array or select a rectangular portion from which to draw its values. This, in the case of SRGraphDisplay, allows many display panels to share data from a single gridded array of data. This makes the construction of multi display or multi axis graphs possible.
//SRGraphDisplay uses a system of dynamic scaling to find the best fit for all information in the graph. Draw cycles are begun with the display having access to the entire surface of the component upon which it is based. As the labels, axis and data are drawn the items are sized and placed, very often in a two pass process to allow the final graph to be shown without having labels overprinting one another or data items overflowing the graph axis area.
//The diminution of the usable area is tracked in the m_DisplayRect member of the SRGraphDisplay object. The size of this rectangle after the draw has taken place is the final size of the data area. This is in fact used by the SRGraphPosition class to detect values and positions when feedback is required from the graph itself
//As with most of the automatic functions in the Objective Char package the automatic sizing may be turned off. using the rectangle locking function. In this case you are responsible for ensuring that adequate room is given to the labels or other items otherwise the graphics may be clipped by the component rectangle itself. This feature is provided to allow the absolute positioning of multiple components. For example you may require two or more display objects to be displayed one above the other. Under normal circumstances the edges of the display will move to accommodate longer or shorter labels and may indeed be re-sized away to nothing if the labels are long enough. By locking the display rectangles into position you can define the exact boundaries and hence the exact alignment of all of the items being displayed thereby ensuring that a particular series is shown in exact proportion to the one above or below it.

//@topic SRGraphDynamicData Class Overview | 
//Based upon SRGraphData this dynamic storage class uses a large memory array of values which may be filled at high speed by successive calls to the SetValue routine or read sequentially by calls to the GetValue member function.
//As data is placed into or taken from the data storage an index is incremented automatically to the next memory array location.
//The buffer itself may be cyclic, that is to say that when the end of the buffer is reached in reading or writing the index will automatically return to zero or it may also be made to grow automatically.
//The best speed for this class is attained when in cyclic mode or when memory is not allowed to grow automatically. The reason for this is the reallocation system which must allocate a completely new block of memory, copy the old data into the new block and delete the old block. For small blocks this wont present much of a problem but as memory sizes get larger the overhead increases exponentially.

//@topic SRGraphException Class Overview | 
//Based upon CException the SRGraphException class allows graceful recovery from errors. Use the TRY {...}, CATCH (SRGraphException,e){...} and END_CATCH macros to enable exception handling in Objective Chart applications.
//
//The exception handler will automatically display a message about the exception if the error goes un-handled. These messages are found in the string table of the SRGraphRes.RC file which must be included in the compile time directives of your application.

//@topic SRGraphFeedback Class Overview | 
//The SRGraphFeedback class holds a polygonal outline for each item of data drawn on screen by the data drawing routines. These shapes may be rectangular bars, pie wedges or the individual faces of the more complex 3d objects. Along with the shape and size of the drawn data the SRGraphFeedback object keeps a record of the group and index to which the data defining the drawn shape belongs.
//After a draw cycle has taken place it is possible to interrogate the SRGraph's list of feedback objects using the mouse pointer coordinates or indeed any x,y position on screen. If the point is found to be inside the feedback polygon the application can derive the actual data address from the data stored in SRGraphFeedback.

//@topic SRGraphRect Class Overview | 
//Like its CRect cousin the SRGraphRect stores rectangular area data. However unlike CRect the SRGraphRect uses a device independent measurement system. While under normal use the described rectangle may be measured in pixels, normal use being on-screen, it may be necessary to use imperial or metric measurement for placement of components wen printing a graph.
//The m_nType member holds the measurement type.

//@topic SRGraphLegend Class Overview | 
//Derived from SRGraphTitle and inheriting the text handling abilities of the base class the legend class displays annotations and coded keys for graphs.
//Like its ancestor SRGraphComponent it has the ability to draw backgrounds, borders and shadows.
//
//Automatic legending
//SRGraphLegend uses the m_pParentGraph pointer to gain access to the m_ComponentList member of the owner graph. It then scans the graph list to see if the item immediately before it in the list is an SRGraphDisplay object. If this is found to be the case SRGraphLegend uses the graph type and scope information in the display to generate an automatic legend which is tailored to the display. If you do not want to use this feature you should either place the SRGraphLegend first in the list or separate it from the display by either another useful component (the graph title or a label perhaps) or put a dummy SRGraphcomponent with zero size before it on the list.

//@topic SRGraphStyle Class Overview | 
//This object holds all the style information for all the components and data items used in SRGraph and Objective Chart generally.
//Each SRGraphData object has a style member to control the visual appearance of the data. Each component has a style which defines how borders are drawn and what background fill is used.
//
//SRGraphStyle has an extensive set of Get and Set functions for changing the individual style settings. This is because most of the styles are held in only a few bits of a DWORD variable. Using the Get and Set functions will ensure that no errors are made thereby inadvertently altering other style settings.
//
//The SRGraphStyle object is very "data light" for its complexity. The same style class is used to manage visual and operational styles for all data items and visual components. The reason for this is that in the fullness of time data items themselves may become visual objects which need component type data. One example of this is the SRGraphData item which stores the floating point data which represents a graph. At the moment the SRGraphStyle component is used to define the type of object drawn for this data. Perhaps a bar or a wiget. In later versions the data may be represented by a full fledged, independent,  3 dimensional component which will require all of the style settings.
//
//Don't be tempted to add functions to adjust the styles directly. To keep data to a minimum the styles from one category are  stored alongside those of another using a bitwise masking system. As the graph style grows in capabilities it may be necessary to expand the scope of the styles. You will be guaranteed to get (and Set) the correct style using the provided methods. However the style bits and codes themselves may be stored in a different place.
//There is no mechanism to allow the expansion or customization of the style class.

//@topic SRGraphTitle Class Overview | 
//Based upon SRGraphComponent the SRGraphTitle object displays the title text from the parent graph.
//This class is also the base class for all other components which use fonts. Like its ancestor it can fill its background, draw borders and cast shadows.

//@topic SRGraphBackground Class Overview | 
//SRGraphBackground is the simplest of all component classes. It is derived from SRGraphComponent but only because SRGraphComponent is not usable in a stand alone manner.
//SRGraphBackground displays no foreground data. This class is used to generate a colored background for other graph components.
//The only extra function performed by the class is to write its name into template files when required to.


//@topic SECComDoc Class Overview | 
//The SECComDoc class is derived from and extends the standard CDocument class. It is used to build document classes (known as ComDocs) which have the ability to invoke, initialise and update other documents based on the same class.
//In the Objective Chart system ComDocs are used to build chart documents which are invoked by and linked to grid documents and which are automatically updated when the grid is edited.
//In order to use this extended class an extended document manager is required. Such a class is provided in the form of SECDocManager which replaces the CDocManager used in the standard MFC architecture.
//
//linking
//ComDocs are the basis both parent and child documents. As one document invokes another it receives a pointer to that new document after the OnFileNew function terminates. (normally under MFC the return type is a void) This pointer is then placed onto the list of linked documents and every time a change takes place in the parent document there is an option of informing the child. Child documents may also invoke, update and be updated by their own child documents.
//In addition to the link from parent to child there is also a link in the opposite direction. This is used to allow a child document to change data in the parent. This is used for example in the objective chart system to allow data items which are dragged in a graph to directly update data in the grid to which the graph is attached.

//@topic SECDocManager Class Overview | 
//This class, based upon CDocManager, adds functionality which allows ComDocs (intercommunicating documents) to function in an MDI application.
//Using SECDocManager and its special document class SECComDoc it is possible to build a single application which manages many document types, each one having the ability to own and communicate with child documents of the same or different types.
//To use SECDocManager you must replace the CDocManager of the CWinApp based class in your application with a SECDocManager, add an overloaded OnFileNew handler to the CWinApp class and register all the different document types in the InitInstance function of that class.
//
//This code shows how these changes were made in the FirstGraph demonstration sample.
//
//First the CDocManager is replaced by SECComDoc by overriding the AddDocTemplate function.
//@iex
//void CFrstGrphApp::AddDocTemplate(CDocTemplate* pTemplate)
//{
//	if (m_pDocManager == NULL)
//		m_pDocManager = new SECDocManager;
//	m_pDocManager->AddDocTemplate(pTemplate);
//}
//@normal
//Then the OnFileNew function is overloaded to provide a new option. That of being able to specify the type of new file and send it initialisation data.
//@iex
//CDocument *CFrstGrphApp::OnFileNew(LPCSTR DocIdent,SEC_UINT nOpCode, SEC_UINT nSubCode,SEC_DWORD dwData,SECComDoc *pParent)
//{
//	if (m_pDocManager != NULL)
//		return ((SECDocManager*)m_pDocManager)->OnFileNew(
//			DocIdent,
//			nOpCode,
//			nSubCode,
//			dwData,
//			pParent);
//	return NULL;
//}
//@normal
//This overload allows a choice of document. For example "Graph" which would be defined in the document template string in the string tables. It also lets the parent document initialise the child document with data defined by the other parameters. For details of ComDoc parameter passing see Binding Objective Chart  to Objective Grid
//
//Finally the declaration of document types in the init instance function.
//@iex
//	CMultiDocTemplate* pDocTemplate;
//	pDocTemplate = new CMultiDocTemplate(
//		IDR_GRIDTYPE,
//		RUNTIME_CLASS(GridDoc),
//		RUNTIME_CLASS(CChildFrame),// custom MDI child frame
//		RUNTIME_CLASS(GridView));
//	AddDocTemplate(pDocTemplate);
//
//	pDocTemplate = new CMultiDocTemplate(
//		IDR_GRAPHTYPE,
//		RUNTIME_CLASS(CGraphDoc),
//		RUNTIME_CLASS(CChildFrame),// custom MDI child frame
//		RUNTIME_CLASS(CGraphView));
//	AddDocTemplate(pDocTemplate);
//@normal
//Here two documents are registered. A grid document using objective grid and a graph document using Objective Chart. For more details see the FirstGraph sample.

//@topic SRGraphView Class Overview | 
//This simple CView based class provides an interface between the MFC window system and the SRGraph object. It handles the mouse input, print pagination and the graph data feedback system.


//@topic SRGDateScale Class Overview | 
//Similar in operation to its SRGDecimalScale ancestor the SGRDateScale class provides a time and date formatted scale based on the formatting capabilities of COleDateTime.
//
//This scale may be used in place of SGRDecimalScale to annotate chart axes.
//
//Note that the use of a double as a date (see COleDateTime for details) means that it is possible to use a value stored in an SRGraphData object as a valid date or time.

//@topic SRGGroupScale Class Overview | 
//This class, like its SRGDecimalScale ancestor, is used to annotate chart axes.
//
//This class takes the annotations from selected group headers to label the axis.

//@topic SRGIndexScale Class Overview | 
//This class, like its SRGDecimalScale ancestor, is used to annotate chart axes.
//
//This class takes the annotations from selected indices to label the axis.

//@topic CGraphDoc Class Overview | 
//The CGraphDoc is a specialised document class based upon SECComDoc that contains an SRGraph storage object and performs serialization and document linking for Objective Chart applications. This class may optionally be used in conjunction with the SRGraphView or SRGScrollView classes to provide an Objective Chart document and view.

//@topic CObStack Class Overview | 
//This simple derivation of the CObList class has "push" and "pop" functions that allow it to be used as a FILO stack. The class is currently used by Objective Chart to store and recover multiple graphic clipping regions and data zoom operations. 

//@topic SRGStructureData Class Overview | 
//This abstract class is the basis for all classes that connect to external data. It provides a standardized set of methods for extracting data from any array of structures. The class maintains a set of pointers and indices that are used to access the data. It is the responsibility of the derived class to extract the information from the data type. The structure data classes are primarily designed to extract data from C-style structures that reside in memory.
//
//Objective Chart assumes that all data to be plotted will be a double precision floating-point number, but the members of the structure may be any numeric data type and may have a different physical size. Therefore, there are a number of classes, based upon SRGStructureData, which handle various data types.
//SRGIntStructData is designed to extract integers.
//SRGFloatStructData extracts single precision floating-point numbers.
//SRGCharStructData extracts byte-sized characters.
//SRGShortStructData extracts short integers.
//SRGDoubleStructData handles double precision floating-point numbers.  
//
//Classes to handle other data types can be derived from SRGStructureData by simply overriding the GetValue and SetValue functions, following the example in these classes.
//
//SRGStructureData is derived from SRGraphDynamicData, so the same access methods are available.  First, Objective Chart needs to know how your memory buffer is configured.  Call SetStructure with a pointer to your memory block, SetStructureSize with the total size of the elemental structure (use sizeof), SetBufferSize with the number of structure elements in the array, and SetDataOffset with the position of the desired data within the structure. Separate positions are maintained for input and output (IncrementInput, DecrementInput, IncrementOutput, DecrementOutput). Then use GetValue and SetValue to access the data at the current position.

//@topic SRGIntStructData Class Overview | 
//SRGIntStructData is derived from SRGStructureData .  It enables Objective Chart to access integer data within an external memory block. Set the base class for details.

//@topic SRGFloatStructData Class Overview | 
//SRGFloatStructData is derived from SRGStructureData .  It enables Objective Chart to access single precision floating-point data within an external memory block. Set the base class for details.

//@topic SRGCharStructData Class Overview | 
//SRGCharStructData is derived from SRGStructureData .  It enables Objective Chart to access byte-sized character data within an external memory block. Set the base class for details.

//@topic SRGShortStructData Class Overview | 
//SRGShortStructData is derived from SRGStructureData .  It enables Objective Chart to access short integer data within an external memory block. See the base class for details.

//@topic SRGDoubleStructData Class Overview | 
//SRGDoubletStructData is derived from SRGStructureData .  It enables Objective Chart to access double precision floating-point data within an external memory block. Set the base class for details.

//@topic SRGDecimalScale Class Overview |
//The Decimal Scale class is a descendant of the standard label block. This class is designed to provide an axis scale annotated with formatted decimal numbers. 
//As with all label block classes this class is anchored to two places in the display or page and the labels are placed along and perpendicular to an imaginary line between those two points.

//@topic SRGLogScale Class Overview |
//The Log Scale class is a descendant of the SRGDecimalScale. This class is designed to provide an axis scale annotated with formatted decimal numbers in a logarithmic scale. 
//As with all label block classes this class is anchored to two places in the display or page and the labels are placed along and perpendicular to an imaginary line between those two points.

//@topic SRGDisplayBase Class Overview |
//This abstract base class contains the function prototypes for all label, axis and data drawing performed by the display classes. 
//The Display base is the point at which two branches of the display class hierarchy, the standard display and the discreet displays, separate.

//@topic SRGWizView Class Overview |
//This derived view class is used in the Chart Wizard. It contains functions for sizing and positioning components with the mouse for design purposes.
//@topic SRGGridLines Class Overview |
//This class draws major and minor grid-lines on the display. Major grid-lines are placed at positions defined by a list of CPoint objects which are created and maintained by an <c SRGraphLabelBlock> based class 
//Minor grid-lines are interspered between major ones. Thier frequency is defined by a Major to Minor line ratio. Grid-lines may be colored or use any of the standard line styles.

//@topic SRGTickMarks Class Overview |
//This class draws major and minor tick-marks on the display. Major tick-marks are placed at positions defined by a list of CPoint objects which are created and maintained by an <c SRGraphLabelBlock> based class 
//Minor tick-marks are interspered between major ones. Thier frequency is defined by a Major to Minor tick ratio. tick-marks may be colored be of different thickness'.

//@topic SRGTextPanel Class Overview |
//This class provides a multi-line text box with a title which may be optionally oriented to the top, bottom or sides of the component. 
//Both title bar and text panel may be idependantly styled.

//@topic SRGCompoundComponent Class Overview |
//The compound component is a specialised class that holds its own component list. When it is drawn by the parent graph then it will draw its own sub-components. Compound components may be nested several layers deep.

//@topic SRGCompoundDisplay Class Overview |
//The compound display, derived from SRGCompoundComponent, maintains a list of axis manager components. Each of these in-turn manage a list of sub-components that are used to create compound charts.

//@topic SRGAxisManager Class Overview |
//This class maintains a list of sub-components which are used to draw a section of a compound display. Each axis manager can optionally manage a display, a datawatcher, a grid-line display class, a tick-mark class and a scale. 
//These classes work in concert to create one axis on a chart.

//@topic CSelectQuery Class Overview |
//This simple dialog is used to resolve ambiguity when selections of data by mouse dragging in the SRGraphView class are made.

//@topic SRGraphTip Class Overview |
//The SRGraphTip class provides a tooltip-like window that is capable of displaying multi-line text. This class is used primarily 
//by the view classes to display chart-tips or drag-tips. The class runs a timer that will remove the window automatically after a few seconds or 
//the class will delete itself when the mouse cursor moves into its area.

//@topic SRGDataWatcher Class Overview |
//The SRGDataWatcher provides a method for monitoring the value of selected data items and generating events if the measured data falls outside of a preset range. The datawatcher is a simple
// component that is placed on the component list before the display. If it detects a data item that is out of bounds it will call one of its excursion flagging routines and set the highlight
// bit in the style of the offending data item. This highlight is then shown by the display and other appropriate action may be taken by functions which override the excursion methods.











