
Object subclass: #Board
	instanceVariableNames: 'values'
	classVariableNames: ''
	package: 'AAA'!

!Board methodsFor: 'accessing' stamp: 'RolandBernard 12/5/2021 00:21'!
values: anObject

	values := anObject! !

!Board methodsFor: 'accessing' stamp: 'RolandBernard 12/5/2021 14:23'!
scoreAt: aTime for: aDictionary

	^ (values flattened select: [ :e | 
		   (aDictionary at: e ifAbsent: [ Float infinity ]) > aTime ]) sum
	* (values flattened select: [ :e | 
		   (aDictionary at: e ifAbsent: [ Float infinity ]) = aTime ]) first! !

!Board methodsFor: 'accessing' stamp: 'RolandBernard 12/5/2021 00:13'!
winTime: aDictionary

	| max |
	max := values collect: [ :l | 
		       (l collect: [ :v | 
			        aDictionary at: v ifAbsent: [ Float infinity ] ]) max ].
	max addAll: ((1 to: values first size) collect: [ :i | 
			 (values collect: [ :l | 
				  aDictionary at: (l at: i) ifAbsent: [ Float infinity ] ]) max ]).
		^ max min! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

Board class
	instanceVariableNames: ''!

!Board class methodsFor: 'as yet unclassified' stamp: 'RolandBernard 12/4/2021 23:55'!
forValues: aColection

	^ self new values:
		  aColection;
		  yourself! !
